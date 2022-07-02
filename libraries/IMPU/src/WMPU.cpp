#include "WMPU.h"
#include "I2Cdev.h"
#include "MPU6050DMPReader.h"
#include "Wire.h"

namespace nsMPU {
    MPU6050 mpu;
    
    // MAXVALUE_INT32 / FULL_SCALE_RANGE * degToRad * 25 (for some reason)
    //const double scale = 2000.0 / 32767.0 * M_PI / 180.0 * 25.0;
    const double scale = 2000.0 / 2147483647.0 * M_PI / 180.0 * 25.0;

    VectorFloat omegaFromAngularVelocity(int32_t* angularVelocity) {
        VectorFloat result(
            angularVelocity[1] * scale,
            angularVelocity[0] * scale,
            -angularVelocity[2] * scale);
        return result;
    }
}

WMPU::WMPU(IEEPromMPU& iEePromMPUManager)
    : eePromMPUManager(iEePromMPUManager)
{
}

int WMPU::begin()
{
    // Join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    Wire.setWireTimeout(3000, true); //timeout value in uSec
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    // Initialize MPU
    nsMPU::mpu.initialize();
    nsMPU::mpu.testConnection();
    uint8_t devStatus; // Return status after each device operation (0 = success, !0 = error)
    devStatus = nsMPU::mpu.dmpInitialize();

    // Guess offsets for when calibration is not used.
    this->guessOffsets();

    return devStatus;
}

bool WMPU::init() {
    // Initialize MPU connection.
    uint8_t devStatus = this->begin();

    // Make sure it worked (returns 0 if so).
    if (devStatus == 0) {

        // Load calibration.
        if (this->isCalibrated()) {
            this->loadCalibration();

            // Turn on the DMP, now that it's ready.
            nsMPU::mpu.setDMPEnabled(true);

            return true;
        }
        else {
            //Serial.println("MPU not calibrated. Waiting execution...");
            return false;
        }
    }
    else {
        //Serial.println("Bad devStatus. Waiting execution...");
        return false;
    }
}

bool WMPU::update()
{
    // Temporary new fifoBuffer;
    uint8_t newFifoBuffer[64];

    // Request new values.
    bool success = nsMPU::mpu.dmpGetCurrentFIFOPacket(newFifoBuffer);

    // If succeeded, update fifoBuffer.
    if (success) {
        for (int i = 0; i < 64; i++) {
            this->fifoBuffer[i] = newFifoBuffer[i];
        }
    }
    return success;
}

bool WMPU::calibrate()
{
    //Serial.println("Assuming MPU is flat and still...");

    uint8_t devStatus = this->begin();
    if (devStatus == 0) {
        // Calibrate
        nsMPU::mpu.CalibrateAccel(6);
        nsMPU::mpu.CalibrateGyro(6);

        // Store values
        this->eePromMPUManager.setXGyroOffset(nsMPU::mpu.getXGyroOffset());
        this->eePromMPUManager.setYGyroOffset(nsMPU::mpu.getYGyroOffset());
        this->eePromMPUManager.setZGyroOffset(nsMPU::mpu.getZGyroOffset());
        this->eePromMPUManager.setXAccelOffset(nsMPU::mpu.getXAccelOffset());
        this->eePromMPUManager.setYAccelOffset(nsMPU::mpu.getYAccelOffset());
        this->eePromMPUManager.setZAccelOffset(nsMPU::mpu.getZAccelOffset());

        this->eePromMPUManager.setMPUCalibFlag();
        //Serial.println("Calibration complete.");

        return true;
    }
    else {
        //Serial.println("Bad devStatus. Waiting execution...");
        return false;
    }
}

bool WMPU::isCalibrated()
{
    return this->eePromMPUManager.getMPUCalibFlag();
}

bool WMPU::resetCalibration()
{
    this->eePromMPUManager.resetMPUCalibFlag();
    return true;
}

void WMPU::guessOffsets() {
    // supply your own gyro offsets here, scaled for min sensitivity
    nsMPU::mpu.setXGyroOffset(220);
    nsMPU::mpu.setYGyroOffset(76);
    nsMPU::mpu.setZGyroOffset(-85);
    nsMPU::mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
}

void WMPU::loadCalibration()
{
    nsMPU::mpu.setXGyroOffset(this->eePromMPUManager.getXGyroOffset());
    nsMPU::mpu.setYGyroOffset(this->eePromMPUManager.getYGyroOffset());
    nsMPU::mpu.setZGyroOffset(this->eePromMPUManager.getZGyroOffset());
    nsMPU::mpu.setXAccelOffset(this->eePromMPUManager.getXAccelOffset());
    nsMPU::mpu.setYAccelOffset(this->eePromMPUManager.getYAccelOffset());
    nsMPU::mpu.setZAccelOffset(this->eePromMPUManager.getZAccelOffset());
}

bool WMPU::getYPR(VectorFloat& ypr) {
    Quaternion q;           // [w, x, y, z]         quaternion container
    bool result = this->getOrientation(q);
    ypr = VectorFloat::yprFromQuaternion(q);
    return result;
}

bool WMPU::getOrientation(Quaternion& q)
{
    uint8_t status = nsMPU::mpu.dmpGetQuaternion(q, fifoBuffer);
    return status == 0;
}

bool WMPU::getAngularVelocity(VectorFloat& omega)
{
    int32_t angularVelocitySensor[3];
    uint8_t status = nsMPU::mpu.dmpGetGyro(angularVelocitySensor, this->fifoBuffer);
    omega = nsMPU::omegaFromAngularVelocity(angularVelocitySensor);
    /*omega.x = angularVelocitySensor[1] * scale;
    omega.y = angularVelocitySensor[0] * scale;
    omega.z = -angularVelocitySensor[2] * scale;*/

    return status == 0;
}

bool WMPU::getAngularVelocity(Quaternion& qdot)
{
    // See https://ahrs.readthedocs.io/en/latest/filters/angular.html#:~:text=Quaternion%20Derivative,-An%20orientation%20is&text=The%20product%20between%20the%20angular,Hamilton%20Product%20can%20be%20applied.
    Quaternion q;
    VectorFloat omega;
    bool result = this->getOrientation(q) && this->getAngularVelocity(omega);
    qdot.w = 0.5 * (-omega.x * q.x - omega.y * q.y - omega.z * q.z);
    qdot.x = 0.5 * (omega.x * q.w + omega.z * q.y - omega.y * q.z);
    qdot.y = 0.5 * (omega.y * q.w - omega.z * q.x + omega.x * q.z);
    qdot.z = 0.5 * (omega.z * q.w + omega.y * q.x - omega.x * q.y);
    return result;
}

bool WMPU::getYPRRate(VectorFloat& yprRate)
{
    // TODO: this is incorrect for large angles.
    VectorFloat angularRate;
    bool result = this->getAngularVelocity(angularRate);
    yprRate.x = angularRate.z;
    yprRate.y = angularRate.y;
    yprRate.z = angularRate.x;
    return false;
}
