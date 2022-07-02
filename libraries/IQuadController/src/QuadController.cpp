#include "QuadController.h"
#include "Arduino.h"

QuadController::QuadController(ISensorManager& sensors, IQuadMotors& quad, IController& controller)
    : sensors(sensors), quad(quad), controller(controller)
{
}

bool QuadController::arm()
{
    bool result = this->quad.arm();
    this->armTime = millis();
    return result;
}

bool QuadController::isArmed()
{
    // TODO: replace by buttonclick or so.
    // 10 seconds after arming.
    return millis() > this->armTime + 15000;
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
    // Arm quadcopter
    bool result = this->arm();
    //Serial.print("Arm motors: ");
    //Serial.println(result);
    
    // Initialize MPU
    if (result) {
        result = result && this->sensors.init();
    }
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

    // Wait for arming
    if (result) {
        while (!this->isArmed());
    }

    return result;
}

bool QuadController::update()
{
    // Update the sensor readings.
    bool result = this->updateSensors();

    // Update the control inputs.
    this->controlLoop();

    return result;
}

bool QuadController::updateSensors()
{
    // Update the sensor readings.
    return this->sensors.update();
}

void QuadController::spin()
{
    // TODO: with frequency?
    while (true) {
        this->update();
    }
}

String QuadController::toString()
{
    return this->sensors.toString();
}
