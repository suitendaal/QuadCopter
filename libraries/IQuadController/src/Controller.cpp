#include "Controller.h"

float mapPi(float value) {
    if (value < -M_PI) {
        while (value < -M_PI) {
            value += 2 * M_PI;
        }
        return value;
    }
    else if (value > M_PI) {
        while (value > M_PI) {
            value -= 2 * M_PI;
        }
        return value;
    }
    return value;
}

bool Controller::init()
{
    this->yawPID.tune(0, 0, 0);
    this->yawPID.constraint(-7, 7);
    this->pitchPID.tune(0, 0, 0);
    this->pitchPID.constraint(-7, 7);
    //this->rollPID.tune(0, 0.5, 0);
    this->rollPID.tune(0, 0, 0);
    this->rollPID.constraint(-7, 7);
    return true;
}

bool Controller::calculate(ISensorManager& sensors, float(&motorSpeeds)[IQuadMotors::Motors])
{
    float motorThrust[IQuadMotors::Motors];

    // Position controller
    VectorFloat orientationRef(0, 0, 0);
    VectorFloat orientationRefDot(0, 0, 0);
    // Between 0.0^2 - 10.0^2
    //float thrustRef = 2.0 * 2.0;
    float velRef = sensors.getRemoteController().getVelRef();
    float Ku = sensors.getRemoteController().getKRef();
    // TODO: We  waren bij vref=20, Ku=30, maar toen bleek dat de limieten van [-7,7] te laag waren.
    
    this->rollPID.tune(Ku, 0, 0);
    
    // Turn off if velRef < 0
    if (velRef < 0) {
        for (int i = 0; i < IQuadMotors::Motors; i++) {
            motorSpeeds[i] = 0;
        }
        return true;
    }

    float thrustRef = velRef * velRef;

    VectorFloat ypr;
    sensors.getMPU().getYPR(ypr);
    VectorFloat yprDot;
    sensors.getMPU().getYPRRate(yprDot);
    VectorFloat error;
    error = orientationRef - ypr;
    VectorFloat errorDot;
    errorDot = orientationRefDot - yprDot;

    error.x = mapPi(error.x);
    error.y = mapPi(error.y);
    error.z = mapPi(error.z);

    Serial.print("Errors: { yaw: ");
    Serial.print(error.x);
    Serial.print(", pitch: ");
    Serial.print(error.y);
    Serial.print(", roll: ");
    Serial.print(error.z);
    Serial.println(" }");

    float yawPart = this->yawPID.compute(error.x, errorDot.x, 0, 0);
    float pitchPart = this->pitchPID.compute(error.y, errorDot.y, 0, 0);
    float rollPart = this->rollPID.compute(error.z, errorDot.z, 0, 0);

    Serial.print("PID: { yaw: ");
    Serial.print(yawPart);
    Serial.print(", pitch: ");
    Serial.print(pitchPart);
    Serial.print(", roll: ");
    Serial.print(rollPart);
    Serial.println(" }");

    // Motor thrust ~ (speed / 10)^2
    motorThrust[0] = thrustRef + yawPart + pitchPart + rollPart;
    motorThrust[1] = thrustRef - yawPart + pitchPart - rollPart;
    motorThrust[2] = thrustRef + yawPart - pitchPart - rollPart;
    motorThrust[3] = thrustRef - yawPart - pitchPart + rollPart;

    for (int i = 0; i < IQuadMotors::Motors; i++) {
        if (motorThrust[i] < 0) {
            motorSpeeds[i] = 0;
        }
        else {
            motorSpeeds[i] = 10.0 * sqrt(motorThrust[i]);
        }
    }

    return true;
}
