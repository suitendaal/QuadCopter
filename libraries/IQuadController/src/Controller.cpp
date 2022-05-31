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
    return true;
}

bool Controller::calculate(ISensorManager& sensors, float(&motorSpeeds)[IQuadMotors::Motors])
{
    float motorThrust[IQuadMotors::Motors];

    // Position controller
    VectorFloat v(0, 0, 0);
    Quaternion orientationRef = v.yprAsQuaternion();
    // Between 0.0^2 - 10.0^2
    //float thrustRef = 2.0 * 2.0;
    float velRef = sensors.getRemoteController().getVelRef();
    
    // Turn off if velRef < 0
    if (velRef < 0) {
        for (int i = 0; i < IQuadMotors::Motors; i++) {
            motorSpeeds[i] = 0;
        }
        return true;
    }

    float thrustRef = velRef * velRef;

    // Orientation controller
    float Kp_yaw = 0.0;// 5.0;
    float Kp_pitch = 10.0;
    float Kp_roll = 0.0;

    VectorFloat ypr;
    sensors.getMPU().getYPR(ypr);
    VectorFloat error;
    error = VectorFloat::yprFromQuaternion(orientationRef) - ypr;

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

    float yawPart = Kp_yaw * error.x;
    float pitchPart = Kp_pitch * error.y;
    float rollPart = Kp_roll * error.z;

    /*Serial.print("PID: { yaw: ");
    Serial.print(yawPart);
    Serial.print(", pitch: ");
    Serial.print(pitchPart);
    Serial.print(", roll: ");
    Serial.print(rollPart);
    Serial.println(" }");*/

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
            motorSpeeds[i] = 100.0 * sqrt(motorThrust[i]);
        }
    }

    return true;
}
