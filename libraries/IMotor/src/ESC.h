#pragma once

#include <Servo.h>
#include "IMotor.h"

class ESC : public IMotor
{
private:
	int pin;
	int minFreq;
	int maxFreq;
	Servo mESC;

	/// <summary>
	/// Maps the speed to a value that can be written to the Servo library.
	/// </summary>
	/// <param name="speed">Speed.</param>
	/// <returns></returns>
	int mapSpeed(int speed);

public:
	/// <summary>
	/// Creates an instance of the ESC class.
	/// </summary>
	ESC();

	/// <summary>
	/// Creates an instance of the ESC class.
	/// </summary>
	/// <param name="pin">ESC pin.</param>
	ESC(int pin);

	/// <summary>
	/// Creates an instance of the ESC class.
	/// </summary>
	/// <param name="pin">ESC pin.</param>
	/// <param name="minFreq">Minimum pwm frequency.</param>
	/// <param name="maxFreq">Maximum pwm frequency.</param>
	ESC(int pin, int minFreq, int maxFreq);

	virtual ~ESC();

	/// <summary>
	/// Attach the ESC to a pin.
	/// </summary>
	/// <param name="pin">ESC pin.</param>
	/// <returns>A boolean indicating whether the attachment succeeded.</returns>
	bool attach(int pin);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool setSpeed(int speed) override;
};

