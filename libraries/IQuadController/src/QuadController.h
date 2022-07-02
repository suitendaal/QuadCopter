#pragma once

#include "IControlManager.h"
#include "ISensorManager.h"
#include "IQuadMotors.h"
#include "IController.h"

class QuadController : public IControlManager
{
private:
	ISensorManager& sensors;
	IQuadMotors& quad;
	IController& controller;
	long int armTime;

	/// <summary>
	/// Arm the quadcopter motors.
	/// </summary>
	/// <returns>A boolean indicating whether the arming succeeded.</returns>
	bool arm();

	/// <summary>
	/// Checks if the motors are armed.
	/// </summary>
	/// <returns>A boolean indicating whether the motors are armed.</returns>
	bool isArmed();

	/// <summary>
	/// Calculate the desired motor speeds.
	/// </summary>
	void controlLoop();

	/// <summary>
	/// Set the motors thrusts to the specified values.
	/// </summary>
	/// <param name="speeds">Desired motor speeds.</param>
	void setMotorSpeeds(float(&speeds)[IQuadMotors::Motors]);
public:
	QuadController(ISensorManager& sensors, IQuadMotors& quad, IController& controller);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool update() override;

	/// <inheritdoc/>
	virtual bool updateSensors() override;

	/// <inheritdoc/>
	virtual void spin() override;

	/// <inheritdoc/>
	virtual String toString() override;
};

