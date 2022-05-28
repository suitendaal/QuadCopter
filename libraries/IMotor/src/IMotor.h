#pragma once

#include "Arduino.h"

class IMotor
{
public:
	const static uint8_t minSpeed = 0;
	const static uint8_t maxSpeed = 255;

	/// <summary>
	/// Initialize the motor up to but not calibration.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Set the motor speed.
	/// </summary>
	/// <param name="speed">Speed, value between 0 and 255.</param>
	/// <returns>A boolean indicating whether the setting succeeded.</returns>
	virtual bool setSpeed(uint8_t speed) = 0;
};

