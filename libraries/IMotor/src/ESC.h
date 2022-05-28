#pragma once

#include <Servo.h>
#include "IMotor.h"

class ESC : public IMotor
{
private:
	int minFreq;
	int maxFreq;
	int pin;
	Servo mESC;

	/// <summary>
	/// Maps the speed to a value that can be written to the Servo library.
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	int mapSpeed(uint8_t speed);;

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

	/// <summary>
	/// Attach the ESC to a pin.
	/// </summary>
	/// <param name="pin">ESC pin.</param>
	/// <returns>A boolean indicating whether the attachment succeeded.</returns>
	bool attach(int pin);

	/// <inheritdoc/>
	virtual bool init() override;

	/// <inheritdoc/>
	virtual bool setSpeed(uint8_t speed) override;
};

