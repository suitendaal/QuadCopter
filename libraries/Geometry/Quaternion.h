// Quaternion.h

#ifndef _Quaternion_h
#define _Quaternion_h

#include "math.h"

class Quaternion {
public:
    float w;
    float x;
    float y;
    float z;

    /// <summary>
    /// Initializes an instance of the Quaternion class.
    /// </summary>
    Quaternion()
        : Quaternion(1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    /// <summary>
    /// Initializes an instance of the Quaternion class.
    /// </summary>
    /// <param name="w">w.</param>
    /// <param name="x">x.</param>
    /// <param name="y">y.</param>
    /// <param name="z">z.</param>
    Quaternion(float w, float x, float y, float z) {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// <summary>
    /// Copy constructor of the Quaternion class.
    /// </summary>
    /// <param name="q">Quaternion to be copied.</param>
    Quaternion(const Quaternion& q)
        : Quaternion(q.w, q.x, q.y, q.z)
    {
    }

    /// <summary>
    /// Multiplies quaternion with another quaternion.
    /// </summary>
    /// <param name="q">Other quaternion.</param>
    /// <returns>Multiplication of quaternions.</returns>
    Quaternion operator*(const Quaternion& q) const {
        // Quaternion multiplication is defined by:
        // (Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
        // (Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
        // (Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
        // (Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2
        return Quaternion(
            this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z,  // new w
            this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,  // new x
            this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,  // new y
            this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w); // new z
    }

    /// <summary>
    /// Gets the conjugate of the quaternion.
    /// </summary>
    /// <returns>Conjugate.</returns>
    Quaternion getConjugate() const {
        return Quaternion(this->w, -this->x, -this->y, -this->z);
    }

    /// <summary>
    /// Gets the magnitude of the quaternion
    /// </summary>
    /// <returns></returns>
    float getMagnitude() const {
        return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
    }

    /// <summary>
    /// Normalizes the quaternion, such that the magnitude is equal to 1.
    /// </summary>
    void normalize() {
        float m = this->getMagnitude();
        this->w /= m;
        this->x /= m;
        this->y /= m;
        this->z /= m;
    }

    /// <summary>
    /// Gets the normalized quaternion.
    /// </summary>
    /// <returns></returns>
    Quaternion getNormalized() const {
        Quaternion q(*this);
        q.normalize();
        return q;
    }
};

#endif
