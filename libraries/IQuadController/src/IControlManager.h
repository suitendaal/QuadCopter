#pragma once

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
	/// Keep updating the controller.
	/// </summary>
	virtual void spin() = 0;
};
