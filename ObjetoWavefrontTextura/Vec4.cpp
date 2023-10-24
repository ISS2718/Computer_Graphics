#include "Vec4.h"

Vec4::Vec4() {}

Vec4::Vec4(const float &x, const float &y,const float &z, const float &w) : x(x), y(y), z(z), w(w) {}

Vec4::Vec4(const float &xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

float Vec4::getX() {
    return x;
}

float Vec4::getY() {
    return y;
}

float Vec4::getZ() {
    return z;
}

float Vec4::getW() {
    return w;
}

void Vec4::set(const float &x, const float &y, const float &z, const float &w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vec4::setX(const float &x) {
    this->x = x;
}

void Vec4::setY(const float &y) {
    this->y = y;
}

void Vec4::setZ(const float &z) {
    this->z = z;
}

void Vec4::setW(const float &w) {
    this->w = w;
}

float Vec4::length() {
    return (float) sqrt(x*x + y*y + z*z + w*w);
}

Vec4& Vec4::normalized() {
    float len = length();
    if(len != 0) {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
    return *this;
}

Vec4& Vec4::abs() {
    x = (float) fabs(x);
    y = (float) fabs(y);
    z = (float) fabs(z);
    w = (float) fabs(w);
    return *this;
}

float Vec4::dot(const Vec4 &v) {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vec4& Vec4::operator=(const float &v) {
    this->x = v;
    this->y = v;
    this->z = v;
    this->w = v;
    return *this;
}

Vec4 Vec4::operator*(const float &v) {
    return Vec4(x * v, y * v, z * v, w * v);
}

Vec4& Vec4::operator*=(const float &v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
}

Vec4 Vec4::operator/(const float &v) {
    if(v != 0) {
        return Vec4(x / v, y / v, z / v, w / v);
    }
    return *this;
}

Vec4& Vec4::operator/=(const float &v) {
    if(v != 0) {
        x /= v;
        y /= v;
        z /= v;
        w /= v;
    }
    return *this;
}

Vec4 Vec4::operator+(const float &v) {
    return Vec4(x + v, y + v, z + v, w + v);
}

Vec4& Vec4::operator+=(const float &v) {
    x += v;
    y += v;
    z += v;
    w += v;
    return *this;
}

Vec4 Vec4::operator-(const float &v) {
    return Vec4(x - v, y - v, z - v, w - v);
}

Vec4& Vec4::operator-=(const float &v) {
    x -= v;
    y -= v;
    z -= v;
    w -= v;
    return *this;
}


Vec4& Vec4::operator=(const Vec4 &v) {
    if(this != &v){
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
    }
    return *this;
}

Vec4 Vec4::operator*(const Vec4 &v) {
    return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vec4& Vec4::operator*=(const Vec4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

Vec4 Vec4::operator/(const Vec4 &v) {
    if(v.x != 0 && v.y != 0){
        return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
    }
    return *this;
}

Vec4& Vec4::operator/=(const Vec4 &v) {
   if(v.x != 0 && v.y != 0){
       x /= v.x;
       y /= v.y;
       z /= v.z;
       w /= v.w;
   }
   return *this;
}

Vec4 Vec4::operator+(const Vec4 &v) {
   return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vec4& Vec4::operator+=(const Vec4 &v) {
   x += v.x;
   y += v.y;
   z += v.z;
   w += v.w;
   return *this;
}

Vec4 Vec4::operator-(const Vec4 &v) {
   return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vec4& Vec4::operator-=(const Vec4 &v) {
   x -= v.x;
   y -= v.y;
   z -= v.z;
   w -= v.w;
   return *this;
}