#pragma once

#include "IController.h"
#include "IMPU.h"
#include "IQuadMotors.h"

class QuadController : public IController
{
private:
	IMPU& mpu;
	IQuadMotors& quad;

	/// <summary>
	/// Arm the quadcopter motors.
	/// </summary>
	/// <returns>A boolean indicating that the arming succeeded.</returns>
	bool arm();
public:
	QuadController(IMPU& mpu, IQuadMotors& quad);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool update() override;
};

