// Pose.h

#ifndef _Pose_h
#define _Pose_h

#include "Vector3.h"
#include "Quaternion.h"

template <typename T>
class Pose {
public:
	Vector3<T> position;
	Quaternion orientation;

	/// <summary>
	/// Initializes a new instance of the Pose class.
	/// </summary>
	Pose<T>()
		: Pose<T>(Vector3<T>(), Quaternion())
	{
	}

	/// <summary>
	/// Initializes a new instance of the Pose class.
	/// </summary>
	/// <param name="position">Position.</param>
	/// <param name="orientation">Orientation.</param>
	Pose<T>(Vector3<T>& position, Quaternion& orientation) {
		this->position = position;
		this->orientation = orientation;
	}

	/// <summary>
	/// Copy constructor of the Pose class.
	/// </summary>
	/// <param name="p">Pose to be copied.</param>
	Pose<T>(const Pose<T>& p)
		: Pose<T>(p.position, p.orientation)
	{
	}
};

#endif
