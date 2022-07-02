#include "SerialController.h"
#include "Arduino.h"

bool SerialController::init()
{
    return true;
}

bool SerialController::update()
{
    while (Serial.available() > 1) {
        this->velRef = Serial.parseFloat();
        this->KRef = Serial.parseFloat();
    }

    return true;
}

float SerialController::getVelRef()
{
    return this->velRef;
}

float SerialController::getKRef()
{
    return this->KRef;
}
