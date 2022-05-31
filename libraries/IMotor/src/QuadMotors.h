#pragma once

#include "IQuadMotors.h"
#include "ESC.h"

class QuadMotors : public IQuadMotors
{
private:
	IMotor** escs = new IMotor*[Motors];

	//IMotor& operator[](int i);

	//ESC operator[](int i) const;
public:
	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	QuadMotors();

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="pins">Motor pins.</param>
	QuadMotors(const int (&pins)[Motors]);

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="pins">Motor pins.</param>
	/// <param name="minFreq">Minimum pwm frequency.</param>
	/// <param name="maxFreq">Maximum pwm frequency.</param>
	QuadMotors(const int (&pins)[Motors], int minFreq, int maxFreq);

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="motors">Motors.</param>
	QuadMotors(IMotor* motors[Motors]);

	virtual ~QuadMotors();

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool arm() override;

	/// <inheritdoc/>
	virtual bool calibrate() override;

	/// <inheritdoc/>
	virtual bool setSpeed(int speeds[Motors]) override;

	/// <inheritdoc/>
	virtual bool setSpeed(int speed) override;
};

