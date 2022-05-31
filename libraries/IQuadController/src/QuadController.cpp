#include "QuadController.h"
#include "Arduino.h"

QuadController::QuadController(ISensorManager& sensors, IQuadMotors& quad, IController& controller)
    : sensors(sensors), quad(quad), controller(controller)
{
}

bool QuadController::arm()
{
    bool result = this->quad.arm();

    // Delay for 7 seconds
    // TODO: replace in future by button click or so.
    delay(10000);

    return result;
}

void QuadController::controlLoop()
{
    // Run the controller update loop.
    float motorSpeeds[IQuadMotors::Motors];
    this->controller.calculate(this->sensors, motorSpeeds);

    // Update motor speeds
    this->setMotorSpeeds(motorSpeeds);
}

void QuadController::setMotorSpeeds(float(&speeds)[IQuadMotors::Motors]) {
    int motorSpeeds[IQuadMotors::Motors];
    for (int i = 0; i < IQuadMotors::Motors; i++) {
        // No conversion necessary.
        motorSpeeds[i] = speeds[i];
    }

    /*Serial.print("Speeds: { ");
    Serial.print(motorSpeeds[0]);
    Serial.print(", ");
    Serial.print(motorSpeeds[1]);
    Serial.print(", ");
    Serial.print(motorSpeeds[2]);
    Serial.print(", ");
    Serial.print(motorSpeeds[3]);
    Serial.println(" }");*/
    this->quad.setSpeed(motorSpeeds);
}

bool QuadController::init()
{
    // Initialize MPU
    bool result = this->sensors.init();
    //Serial.print("MPU init: ");
    //Serial.println(result);

    // Initialize quadcopter
    if (result) {
        result = result && this->quad.init();
    }
    //Serial.print("Quad init: ");
    //Serial.println(result);

    // Initialize controllers
    if (result) {
        result = result && this->controller.init();
    }
    //Serial.print("Controller init: ");
    //Serial.println(result);

    // Arm quadcopter
    if (result) {
        result = result && this->arm();
    }
    //Serial.print("Arm motors: ");
    //Serial.println(result);

    return result;
}

bool QuadController::update()
{
    // Update the sensor readings.
    this->sensors.update();

    // Update the control inputs.
    this->controlLoop();

    return true;
}

void QuadController::spin()
{
    // TODO: with frequency?
    while (true) {
        this->update();
    }
}
