#include "Quaternion.hpp"
#include <cmath>

Quaternion::Quaternion(const Vector3 &v, double angle){
    angle = angle/2 * M_PI/180;
    this->re = cos(angle);
    this->im = v * sin(angle);

    this->im = this->im / this->im.Length();
}



Vector3 Quaternion::operator*(const Vector3 &v) const{
    return  v * this->im;
}

Vector3& operator*=(Vector3 &v, const Quaternion &q) {
    v *=q.im;
    return v;
}