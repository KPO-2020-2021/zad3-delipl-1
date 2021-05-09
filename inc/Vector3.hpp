#ifndef __VECTOR3_HPP__
#define __VECTOR3_HPP__
#include "Vector.hpp"
/**
 * @brief three dimentional double Vector
 */
typedef Vector<double, 3> Vector3;

/**
 * @brief two dimentional double Vector
 */
typedef Vector<double, 2> Vector2;

/**
 * @brief X axis Vector3
 */
static Vector3 VectorX = {1, 0, 0};

/**
 * @brief Y axis Vector3
 */
static Vector3 VectorY = {0, 1, 0};

/**
 * @brief Z axis Vector3
 */
static Vector3 VectorZ = {0, 0, 1};

/**
 * @brief 3 dimentional Cross Product
 */
template<>
Vector3 Vector3::operator*(const Vector3 &v) const;

/**
 * @brief 3 dimentional Cross Product
 */
template<>
Vector3 &Vector3::operator*=(const Vector3 &v);


#endif // __VECTOR3_HPP__