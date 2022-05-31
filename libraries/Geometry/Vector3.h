// Vector3.h

#ifndef _Vector3_h
#define _Vector3_h

#include "math.h"
#include "stdint.h"
#include "Quaternion.h"

template <typename T>
class Vector3
{
public:
    T x;
    T y;
    T z;

    /// <summary>
    /// Initializes an instance of the Vector3 class.
    /// </summary>
    /// <typeparam name="T">Data type.</typeparam>
    Vector3<T>()
        : Vector3<T>(0, 0, 0)
    {
    }
    
    /// <summary>
    /// Initializes an instance of the Vector3 class.
    /// </summary>
    /// <param name="x">x.</param>
    /// <param name="y">y.</param>
    /// <param name="z">z.</param>
    Vector3<T>(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// <summary>
    /// Copy constructor of the Vector3 class.
    /// </summary>
    /// <param name="v">Vector to be copied.</param>
    Vector3<T>(Vector3<T> &v)
        : Vector3<T>(v.x, v.y, v.z)
    {
    }

    virtual Vector3<T> operator-(Vector3<T>& other) const {
        Vector3<T> result;
        result.x = this->x - other.x;
        result.y = this->y - other.y;
        result.z = this->z - other.z;
        return result;
    }

    /// <summary>
    /// Gets the magnitude of the vector.
    /// </summary>
    /// <returns>Magnitude.</returns>
    float getMagnitude() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    /// <summary>
    /// Normalizes the data.
    /// </summary>
    void normalize() {
        float m = this->getMagnitude();
        this->x /= m;
        this->y /= m;
        this->z /= m;
    }

    /// <summary>
    /// Gets the normalized vector.
    /// </summary>
    /// <returns>Normalized vector.</returns>
    Vector3<T> getNormalized() const {
        Vector3<T> v(*this);
        v.normalize();
        return v;
    }

    /// <summary>
    /// Rotates the point around a quaternion.
    /// </summary>
    /// <param name="q">Quaternion.</param>
    void rotate(Quaternion& q) {
        Quaternion p(0, x, y, z);

        // quaternion multiplication: q * p, stored back in p
        p = q * p;

        // quaternion multiplication: p * conj(q), stored back in p
        p = p * q.getConjugate();

        // p quaternion is now [0, x', y', z']
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }

    /// <summary>
    /// Gets the rotated vector around a quaternion.
    /// </summary>
    /// <param name="q">Quaternion.</param>
    Vector3<T> getRotated(Quaternion& q) const {
        Vector3<T> v(*this);
        v.rotate(q);
        return v;
    }

    Quaternion yprAsQuaternion() const {
        Quaternion q;
        q.w = cos(this->z / 2) * cos(this->y / 2) * cos(this->x / 2)
            + sin(this->z / 2) * sin(this->y / 2) * sin(this->x / 2);
        q.x = sin(this->z / 2) * cos(this->y / 2) * cos(this->x / 2)
            - cos(this->z / 2) * sin(this->y / 2) * sin(this->x / 2);
        q.y = cos(this->z / 2) * sin(this->y / 2) * cos(this->x / 2)
            + sin(this->z / 2) * cos(this->y / 2) * sin(this->x / 2);
        q.z = cos(this->z / 2) * cos(this->y / 2) * sin(this->x / 2)
            - sin(this->z / 2) * sin(this->y / 2) * cos(this->x / 2);
        return q;
    }
};

class VectorInt16 : public Vector3<uint16_t> {
    using Vector3::Vector3;
};

class VectorFloat : public Vector3<float> {
    using Vector3::Vector3;
public:
    virtual VectorFloat operator-(VectorFloat& other) const {
        VectorFloat result(this->x - other.x, this->y - other.y, this->z - other.z);
        return result;
    }

    /// <summary>
    /// Calculates the yaw, pitch and roll based on a quaternion.
    /// </summary>
    /// <param name="q">Quaternion.</param>
    /// <returns>Yaw, pitch and roll.</returns>
    static VectorFloat yprFromQuaternion(Quaternion& q) {
        VectorFloat v;
        
        // Yaw
        v.x = -atan2(-2 * q.x * q.y + 2 * q.w * q.z, q.y * q.y - q.z * q.z - q.x * q.x + q.w * q.w);

        // Pitch
        v.y = asin(2 * q.y * q.z + 2 * q.w * q.x);

        // Roll
        v.z = atan2(-2 * q.x * q.z + 2 * q.w * q.y, q.z * q.z - q.y * q.y - q.x * q.x + q.w * q.w);

        return v;
    }
};

#endif

