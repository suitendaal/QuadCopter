#pragma once

#include "IMotor.h"

class IQuadMotors
{
public:
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
	/// <param name="speed1">Motor 1 speed, value between 0 and 255.</param>
	/// <param name="speed2">Motor 2 speed, value between 0 and 255.</param>
	/// <param name="speed3">Motor 3 speed, value between 0 and 255.</param>
	/// <param name="speed4">Motor 4 speed, value between 0 and 255.</param>
	/// <returns>A boolean indicating whether the setting of the speed succeeded.</returns>
	virtual bool setSpeed(uint8_t speed1, uint8_t speed2, uint8_t speed3, uint8_t speed4) = 0;

	/// <summary>
	/// Set motor speeds.
	/// </summary>
	/// <param name="speed">Motor speed, value between 0 and 255.</param>
	/// <returns>A boolean indicating whether the setting of the speed succeeded.</returns>
	virtual bool setSpeed(uint8_t speed) = 0;
};

