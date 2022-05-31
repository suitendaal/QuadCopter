#pragma once

#include "Arduino.h"

class IMotor
{
public:
	const static int MinSpeed = 0;
	const static int MaxSpeed = 1000;

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~IMotor() {};

	/// <summary>
	/// Initialize the motor up to but not calibration.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Set the motor speed.
	/// </summary>
	/// <param name="speed">Speed, value between 0 and 1000.</param>
	/// <returns>A boolean indicating whether the setting succeeded.</returns>
	virtual bool setSpeed(int speed) = 0;
};

