#include "WMPU.h"
#include "I2Cdev.h"
#include "MPU6050DMPReader.h"
#include "Wire.h"

namespace nsMPU {
    MPU6050 mpu;
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

bool WMPU::getYPR(VectorFloat& ypr) {
    Quaternion q;           // [w, x, y, z]         quaternion container
    uint8_t status = nsMPU::mpu.dmpGetQuaternion(q, fifoBuffer);
    ypr = VectorFloat::yprFromQuaternion(q);
    return status == 0;
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
