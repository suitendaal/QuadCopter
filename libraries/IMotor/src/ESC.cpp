#include "ESC.h"

ESC::ESC()
    : ESC(3)
{
}

ESC::ESC(int pin)
    : ESC(pin, 1000, 2000)
{
}

ESC::ESC(int pin, int minFreq, int maxFreq)
    : pin(pin), minFreq(minFreq), maxFreq(maxFreq)
{
}

ESC::~ESC()
{
}

bool ESC::attach(int pin)
{
    this->pin = pin;
    return (this->mESC.attach(pin, this->minFreq, this->maxFreq) != INVALID_SERVO);
}

bool ESC::init()
{
    return this->attach(this->pin);
}

bool ESC::setSpeed(int speed)
{
    this->mESC.writeMicroseconds(this->mapSpeed(speed));
    return true;
}

int ESC::mapSpeed(int speed)
{
    // Put between minspeed and maxspeed.
    speed = speed < MinSpeed ? MinSpeed : speed > MaxSpeed ? MaxSpeed : speed;
    return ((float)(speed - IMotor::MinSpeed) / (IMotor::MaxSpeed - IMotor::MinSpeed)) * (this->maxFreq - this->minFreq) + this->minFreq;
}
