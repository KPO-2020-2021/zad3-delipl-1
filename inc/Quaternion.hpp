#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__
#include "Vector3.hpp"

class Quaternion{
    public:
    /**
     * @brief Scalar cord of Quaternion
     */
    double re;

    /**
     * @brief Imaginary Vector with 3 complex units i j k
     */
    Vector3 im;

    /**
     * @brief Construct a new Quaternion object
     * @param v axis rotate vector
     * @param angle to rotate
     */
    Quaternion(const Vector3 &v, double angle);

    /**
     * @brief Multiplaying Vector3 and Quaternion rotates Vector3
     * @param v point to rotate 
     * @return Vector3 rotated point
     */
    Vector3 operator*(const Vector3 &v) const;
};

Vector3 &operator*=(Vector3 &v, const Quaternion &q);
#endif // __QUATERNION_HPP__