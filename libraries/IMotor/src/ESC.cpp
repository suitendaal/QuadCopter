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

bool ESC::attach(int pin)
{
    this->pin = pin;
    return (this->mESC.attach(pin, this->minFreq, this->maxFreq) != INVALID_SERVO);
}

bool ESC::init()
{
    return this->attach(this->pin);
}

bool ESC::setSpeed(uint8_t speed)
{
    this->mESC.writeMicroseconds(this->mapSpeed(speed));
    return true;
}

int ESC::mapSpeed(uint8_t speed)
{
    return ((float)speed / 255) * (this->maxFreq - this->minFreq) + this->minFreq;
}
