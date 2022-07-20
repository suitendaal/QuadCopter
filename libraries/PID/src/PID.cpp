#include "PID.h"

PID::PID()
    : PID(0, 0, 0)
{
}

PID::PID(float Kp, float Kd, float Ki)
    : Kp(Kp), Kd(Kd), Ki(Ki)
{
}

void PID::tune(float Kp, float Kd, float Ki)
{
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
}

void PID::constraint(float underLimit, float upperLimit)
{
    this->limit = true;
    this->underLimit = underLimit;
    this->upperLimit = upperLimit;
}

float PID::compute(float error, float errorDot, long int now)
{
    if (this->lastTime >= 0) {
        this->integral += this->Ki * error * (now - this->lastTime) / 1000.0;
        if (this->limit)
        {
            this->integral = this->integral < this->underLimit ? this->underLimit :
                this->integral > this->upperLimit ? this->upperLimit : this->integral;
        }
    }



    float proportionalPart = this->Kp * error;
    float derivativePart = this->lastTime >= 0 ? this->Kd * errorDot : 0;
    float integralPart = this->integral;
    float result = proportionalPart + derivativePart + integralPart;
    if (this->limit)
    {
        result = result < this->underLimit ? this->underLimit :
            result > this->upperLimit ? this->upperLimit : result;
    }

    this->lastTime = now;
    this->previousError = error;
    return result;
}

float PID::compute(float setPoint, float value)
{
    long int now = millis();
    float error = setPoint - value;

    float errorDot = 0;
    if (this->lastTime >= 0) {
        errorDot = (error - this->previousError) / ((now - this->lastTime) / 1000.0);
    }

    return this->compute(error, errorDot, now);
}

float PID::compute(float setPoint, float setPointDot, float value, float valueDot)
{
    return this->compute(setPoint - value, setPointDot - valueDot, millis());
}
