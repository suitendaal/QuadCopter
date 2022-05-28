#include "QuadMotors.h"

QuadMotors::QuadMotors()
    : QuadMotors(3, 5, 6, 7)
{
}

QuadMotors::QuadMotors(int pin1, int pin2, int pin3, int pin4)
{
    this->escs[0] = ESC(pin1);
    this->escs[1] = ESC(pin2);
    this->escs[2] = ESC(pin3);
    this->escs[3] = ESC(pin4);
}

QuadMotors::QuadMotors(int pin1, int pin2, int pin3, int pin4, int minFreq, int maxFreq)
{
    this->escs[0] = ESC(pin1, minFreq, maxFreq);
    this->escs[1] = ESC(pin2, minFreq, maxFreq);
    this->escs[2] = ESC(pin3, minFreq, maxFreq);
    this->escs[3] = ESC(pin4, minFreq, maxFreq);
}

QuadMotors::QuadMotors(ESC esc1, ESC esc2, ESC esc3, ESC esc4)
{
    this->escs[0] = esc1;
    this->escs[1] = esc2;
    this->escs[2] = esc3;
    this->escs[3] = esc4;
}

bool QuadMotors::init()
{
    for (int i = 0; i < 4; i++) {
        this->escs[i].init();
    }
}

bool QuadMotors::arm()
{
    Serial.println("Arming ESCs.");
    bool result = this->setSpeed(0);
    if (!result) {
        Serial.println("Something went wrong...");
        return result;
    }

    Serial.println("Please connect ESCs");
    return result;
}

bool QuadMotors::calibrate()
{
    // Boolean indicating that calibration succeeds.
    bool result = true;
    Serial.println("ESCs should be connected by now.");
    Serial.println("Setting maximum throttle.");
    this->setSpeed(IMotor::maxSpeed);

    if (!result) {
        Serial.println("Something went wrong...");
        return result;
    }

    Serial.println("Wait for 3 seconds.");
    delay(3000);

    Serial.println("Setting minimum throttle.");
    this->setSpeed(IMotor::minSpeed);

    if (!result) {
        Serial.println("Something went wrong...");
        return result;
    }

    Serial.println("Wait for 3 seconds.");
    delay(3000);

    Serial.println("Calibration is done.");

    return result;
}

bool QuadMotors::setSpeed(uint8_t speed1, uint8_t speed2, uint8_t speed3, uint8_t speed4)
{
    bool result = true;
    result = result && this->escs[0].setSpeed(speed1);
    result = result && this->escs[1].setSpeed(speed2);
    result = result && this->escs[2].setSpeed(speed3);
    result = result && this->escs[3].setSpeed(speed4);

    return result;
}

bool QuadMotors::setSpeed(uint8_t speed)
{
    bool result = true;
    for (int i = 0; i < 4; i++) {
        result = result && this->escs[i].setSpeed(speed);
    }

    return result;
}
