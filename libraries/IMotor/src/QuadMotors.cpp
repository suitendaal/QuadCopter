#include "QuadMotors.h"
#include "Arduino.h"

QuadMotors::QuadMotors()
    : QuadMotors({ 3, 5, 6, 7 })
{
}

QuadMotors::QuadMotors(const int(&pins)[Motors])
{
    for (int i = 0; i < Motors; i++) {
        this->escs[i] = new ESC(pins[i]);
    }
}

QuadMotors::QuadMotors(const int(&pins)[Motors], int minFreq, int maxFreq)
{
    for (int i = 0; i < Motors; i++) {
        this->escs[i] = new ESC(pins[i], minFreq, maxFreq);
    }
}

QuadMotors::QuadMotors(IMotor* motors[Motors])
{
    for (int i = 0; i < Motors; i++) {
        this->escs[i] = motors[i];
    }
}

QuadMotors::~QuadMotors()
{
    for (int i = 0; i < Motors; i++) {
        delete this->escs[i];
    }
    delete[] this->escs;
}

bool QuadMotors::init()
{
    for (int i = 0; i < Motors; i++) {
        //(*this)[i].init();
        this->escs[i]->init();
    }

    return true;
}

bool QuadMotors::arm()
{
    //Serial.println("Arming ESCs.");
    bool result = this->setSpeed(0);
    if (!result) {
        //Serial.println("Something went wrong...");
        return result;
    }

    Serial.println("Please connect ESCs");
    return result;
}

bool QuadMotors::calibrate()
{
    // Boolean indicating that calibration succeeds.
    bool result = true;
    //Serial.println("ESCs should be connected by now.");
    //Serial.println("Setting maximum throttle.");
    this->setSpeed(IMotor::MaxSpeed);

    if (!result) {
        //Serial.println("Something went wrong...");
        return result;
    }

    //Serial.println("Wait for 3 seconds.");
    delay(3000);

    //Serial.println("Setting minimum throttle.");
    this->setSpeed(IMotor::MinSpeed);

    if (!result) {
        //Serial.println("Something went wrong...");
        return result;
    }

    //Serial.println("Wait for 3 seconds.");
    delay(3000);

    Serial.println("Calibration is done.");

    return result;
}

bool QuadMotors::setSpeed(int speeds[Motors])
{
    bool result = true;
    for (int i = 0; i < Motors; i++) {
        result = result && this->escs[i]->setSpeed(speeds[i]);
        //result = result && (*this)[i].setSpeed(speeds[i]);
    }

    return result;
}

bool QuadMotors::setSpeed(int speed)
{
    bool result = true;
    for (int i = 0; i < Motors; i++) {
        result = result && this->escs[i]->setSpeed(speed);
        //result = result && (*this)[i].setSpeed(speed);
    }

    return result;
}
