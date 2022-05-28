#include "QuadController.h"
#include "Arduino.h"

QuadController::QuadController(IMPU& mpu, IQuadMotors& quad)
    : mpu(mpu), quad(quad)
{
}

bool QuadController::arm()
{
    bool result = this->quad.arm();

    // Delay for 7 seconds
    // TODO: replace in future by button click or so.
    delay(7000);

    return result;
}

bool QuadController::init()
{
    // Initialize MPU
    bool result = this->mpu.init();

    // Initialize quadcopter
    if (result) {
        result = result && this->quad.init();
    }

    // Arm quadcopter
    if (result) {
        result = result && this->arm();
    }
    return result;
}

bool QuadController::update()
{
    return true;
}
