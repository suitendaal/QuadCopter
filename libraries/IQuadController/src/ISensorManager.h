#pragma once

#include "IMPU.h"
#include "IRemoteController.h"
#include "Arduino.h"

class ISensorManager
{
public:
	/// <summary>
	/// Initialize the sensors.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Update the sensors.
	/// </summary>
	/// <returns>A boolean indicating whether the updating succeeded.</returns>
	virtual bool update() = 0;

	/// <summary>
	/// Gets the MPU.
	/// </summary>
	/// <returns>MPU.</returns>
	virtual IMPU& getMPU() = 0;

	/// <summary>
	/// Gets the remote controller.
	/// </summary>
	/// <returns>Remote controller.</returns>
	virtual IRemoteController& getRemoteController() = 0;

	/// <summary>
	/// Converts sensorvalues to string.
	/// </summary>
	/// <returns>Sensorvalues as string.</returns>
	virtual String toString() = 0;
};

