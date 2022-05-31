#pragma once

#include "ISensorManager.h"
#include "IQuadMotors.h"

class IController
{
public:
	/// <summary>
	/// Initializes the orientation controller.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Calculate the desired motor speeds.
	/// </summary>
	/// <param name="sensors">Sensors.</param>
	/// <param name="motorThrust">Desired motor speed result.</param>
	/// <returns>A boolean indicating whether the calculation succeeded.</returns>
	virtual bool calculate(ISensorManager& sensors, float(&motorSpeeds)[IQuadMotors::Motors]) = 0;
};
