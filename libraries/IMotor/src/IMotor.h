#pragma once

class IMotor
{
public:
	/// <summary>
	/// Set the motor speed.
	/// </summary>
	/// <param name="speed">Speed, value between 0 and 255.</param>
	/// <returns>A boolean indicating whether the setting succeeded.</returns>
	virtual bool setSpeed(uint8_t speed) = 0;
};

