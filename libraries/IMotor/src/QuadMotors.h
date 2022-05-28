#pragma once

#include "IQuadMotors.h"
#include <ESC.h>

class QuadMotors : public IQuadMotors
{
private:
	ESC escs[4];
public:
	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	QuadMotors();

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="pin1">Motor 1 pin.</param>
	/// <param name="pin2">Motor 2 pin.</param>
	/// <param name="pin3">Motor 3 pin.</param>
	/// <param name="pin4">Motor 4 pin.</param>
	QuadMotors(int pin1, int pin2, int pin3, int pin4);

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="pin1">Motor 1 pin.</param>
	/// <param name="pin2">Motor 2 pin.</param>
	/// <param name="pin3">Motor 3 pin.</param>
	/// <param name="pin4">Motor 4 pin.</param>
	/// <param name="minFreq">Minimum pwm frequency.</param>
	/// <param name="maxFreq">Maximum pwm frequency.</param>
	QuadMotors(int pin1, int pin2, int pin3, int pin4, int minFreq, int maxFreq);

	/// <summary>
	/// Creates an instance of the QuadMotors class.
	/// </summary>
	/// <param name="esc1">ESC 1.</param>
	/// <param name="esc2">ESC 2.</param>
	/// <param name="esc3">ESC 3.</param>
	/// <param name="esc4">ESC 4.</param>
	QuadMotors(ESC esc1, ESC esc2, ESC esc3, ESC esc4);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool arm() override;

	/// <inheritdoc/>
	virtual bool calibrate() override;

	/// <inheritdoc/>
	virtual bool setSpeed(uint8_t speed1, uint8_t speed2, uint8_t speed3, uint8_t speed4) override;

	/// <inheritdoc/>
	virtual bool setSpeed(uint8_t speed) override;
};

