#pragma once

#include "Geometry.h"

/// <summary>
/// Abstract class of mpu adapter.
/// </summary>
class IMPU
{
public:
	/// <summary>
	/// Initialize the MPU.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization has succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Reads the new values from the MPU.
	/// </summary>
	/// <returns>A boolean indicating whether the updating has succeeded.</returns>
	virtual bool update() = 0;

	/// <summary>
	/// Gets the yaw, pitch, and roll.
	/// </summary>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getYPR(VectorFloat& ypr) = 0;

	/// <summary>
	/// Calibrate the MPU.
	/// </summary>
	/// <returns>Boolean indicating whether the calibration succeeded.</returns>
	virtual bool calibrate() = 0;

	/// <summary>
	/// Check if the MPU is calibrated.
	/// </summary>
	/// <returns>A boolean indicating that the MPU is calibrated.</returns>
	virtual bool isCalibrated() = 0;

	/// <summary>
	/// Reset the calibration to uncalibrated.
	/// </summary>
	/// <returns>A boolean indicating whether the resetting succeeded.</returns>
	virtual bool resetCalibration() = 0;
};
