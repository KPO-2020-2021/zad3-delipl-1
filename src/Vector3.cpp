#include "Vector3.hpp"


template<>
Vector3 Vector3::operator*(const Vector3 &v) const{
    auto u = Vector3(v);
    u[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    u[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    u[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
    return u;
}
template<>
Vector3 &Vector3::operator*=(const Vector3 &v) {
    (*this)[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    (*this)[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    (*this)[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
    return *this;
}
