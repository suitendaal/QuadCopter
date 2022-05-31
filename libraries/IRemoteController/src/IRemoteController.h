#pragma once

class IRemoteController
{
public:
	/// <summary>
	/// Initialize the remote controller.
	/// </summary>
	/// <returns>A boolean indicating whether the initialization has succeeded.</returns>
	virtual bool init() = 0;

	/// <summary>
	/// Retrieve new values from the remote controller.
	/// </summary>
	/// <returns>A boolean indicating whether the update has succeeded.</returns>
	virtual bool update() = 0;

	virtual float getVelRef() = 0;
};

