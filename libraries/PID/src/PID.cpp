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

float PID::compute(float setPoint, float value)
{
    long int now = millis();
    float error = setPoint - value;
    
    float derivative = 0;
    if (this->lastTime >= 0) {
        float timeDiff = now - this->lastTime;
        derivative = (error - this->previousError) / timeDiff;
        this->integral += error * timeDiff;
        if (this->limit)
        {
            this->integral = this->integral < this->underLimit / this->Ki ? this->underLimit / this->Ki :
                this->integral > this->upperLimit / this->Ki ? this->upperLimit / this->Ki : this->integral;
        }
    }

    

    float proportionalPart = this->Kp * error;
    float derivativePart = this->lastTime >= 0 ? this->Kd * derivative : 0;
    float integralPart = this->Ki * this->integral;
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
