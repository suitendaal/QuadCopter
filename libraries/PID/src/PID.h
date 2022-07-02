#pragma once

#include "Arduino.h"

class PID
{
private:
	// Terms
	float Kp;
	float Kd;
	float Ki;

	float integral = 0;
	long int lastTime = -1;
	float previousError = 0;

	bool limit = false;
	float underLimit = -1000;
	float upperLimit = 1000;

	float compute(float error, float errorDot, long int now);

public:
	PID();
	PID(float Kp, float Kd, float Ki);
	void tune(float Kp, float Kd, float Ki);
	void constraint(float underLimit, float upperLimit);
	float compute(float setPoint, float value);
	float compute(float setPoint, float setPointDot, float value, float valueDot);
};

