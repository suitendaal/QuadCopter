#pragma once

#include "Arduino.h"

class IControlManager
{
public:
	/// <summary>
	/// Initialize the controller.
	/// </summary>
	/// <returns>A boolean indicating whether the intialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Update the controller.
	/// </summary>
	/// <returns>A boolean indicating whether the updating succeeded.</returns>
	virtual bool update() = 0;

	/// <summary>
	/// Update the sensors only.
	/// </summary>
	/// <returns>A boolean indicating whether the updating succeeded.</returns>
	virtual bool updateSensors() = 0;

	/// <summary>
	/// Keep updating the controller.
	/// </summary>
	virtual void spin() = 0;

	/// <summary>
	/// Converts values from sensor to string.
	/// </summary>
	/// <returns>Sensorvalues as string.</returns>
	virtual String toString() = 0;
};
