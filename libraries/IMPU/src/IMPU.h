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

	/// <summary>
	/// Gets the yaw, pitch, and roll.
	/// </summary>
	/// <param name="ypr">Yaw, pitch, roll vector result.</param>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getYPR(VectorFloat& ypr) = 0;

	/// <summary>
	/// Gets the orientation as quaternion.
	/// </summary>
	/// <param name="q">Orientation quaternion result.</param>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getOrientation(Quaternion& q) = 0;

	/// <summary>
	/// Gets the angular velocity vector.
	/// </summary>
	/// <param name="omega">Angular velocity result.</param>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getAngularVelocity(VectorFloat& omega) = 0;

	/// <summary>
	/// Gets the angular velocity vector.
	/// </summary>
	/// <param name="qdot">Angular velocity result.</param>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getAngularVelocity(Quaternion& qdot) = 0;

	/// <summary>
	/// Gets the yaw pitch roll rate vector.
	/// </summary>
	/// <param name="yprRate">Yaw pitch roll rate result.</param>
	/// <returns>A boolean indicating whether the request succeeded.</returns>
	virtual bool getYPRRate(VectorFloat& yprRate) = 0;
};
