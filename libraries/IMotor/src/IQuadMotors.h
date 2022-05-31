#pragma once

#include "IMotor.h"

class IQuadMotors
{
public:
	const static int MinSpeed = IMotor::MinSpeed;
	const static int MaxSpeed = IMotor::MaxSpeed;
	const static uint8_t Motors = 4;

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~IQuadMotors() {};

	/// <summary>
	/// Initialize the quadmotors.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Arm the motors.
	/// </summary>
	/// <returns>A boolean indicating whether the arming succeeded.</returns>
	virtual bool arm() = 0;

	/// <summary>
	/// Calibrate the motors.
	/// </summary>
	/// <returns>A boolean indicating whether the calibration succeeded.</returns>
	virtual bool calibrate() = 0;

	/// <summary>
	/// Set motor speeds.
	/// </summary>
	/// <param name="speeds">Motor speeds.</param>
	/// <returns>A boolean indicating whether the setting of the speed succeeded.</returns>
	virtual bool setSpeed(int speeds[Motors]) = 0;

	/// <summary>
	/// Set motor speeds.
	/// </summary>
	/// <param name="speed">Motor speed, value between 0 and 1000.</param>
	/// <returns>A boolean indicating whether the setting of the speed succeeded.</returns>
	virtual bool setSpeed(int speed) = 0;
};

