#include "Vec3.h"

Vec3::Vec3() {}

Vec3::Vec3(const float &x,const float &y,const float &z) : x(x), y(y), z(z) {}

Vec3::Vec3(const float &xyz) : x(xyz), y(xyz), z(xyz) {}

float Vec3::getX() {
    return x;
}

float Vec3::getY() {
    return y;
}

float Vec3::getZ() {
    return z;
}

void Vec3::set(const float &x, const float &y, const float &z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec3::setX(const float &x) {
    this->x = x;
}

void Vec3::setY(const float &y) {
    this->y = y;
}

void Vec3::setZ(const float &z) {
    this->z = z;
}

float Vec3::length() {
    return (float) sqrt(x*x + y*y + z*z);
}

Vec3& Vec3::normalized() {
    float len = length();
    if(len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }
    return *this;
}

Vec3& Vec3::abs() {
    x = (float) fabs(x);
    y = (float) fabs(y);
    z = (float) fabs(z);
    return *this;
}

float Vec3::dot(const Vec3 &v) {
    return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::cross(const Vec3& v)
{
    Vec3 crossv;
    crossv.x = y * v.z - z * v.y;
    crossv.y = z * v.x - x * v.z;
    crossv.z = x * v.y - y * v.x;
    return crossv;
}

Vec3& Vec3::operator=(const float &v) {
    this->x = v;
    this->y = v;
    this->z = v;
    return *this;
}

Vec3 Vec3::operator*(const float &v) {
    return Vec3(x * v, y * v, z * v);
}

Vec3& Vec3::operator*=(const float &v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
}

Vec3 Vec3::operator/(const float &v) {
    if(v != 0) {
        return Vec3(x / v, y / v, z / v);
    }
    return *this;
}

Vec3& Vec3::operator/=(const float &v) {
    if(v != 0) {
        x /= v;
        y /= v;
        z /= v;
    }
    return *this;
}

Vec3 Vec3::operator+(const float &v) {
    return Vec3(x + v, y + v, z + v);
}

Vec3& Vec3::operator+=(const float &v) {
    x += v;
    y += v;
    z += v;
    return *this;
}

Vec3 Vec3::operator-(const float &v) {
    return Vec3(x - v, y - v, z - v);
}

Vec3& Vec3::operator-=(const float &v) {
    x -= v;
    y -= v;
    z -= v;
    return *this;
}

bool Vec3::operator==(const float &v) {
    if((x == v) && (y == v) && (z == v)) {
        return true;
    }
    return false;
}

bool Vec3::operator>=(const float &v) {
    if((x >= v) && (y >= v) && (z >= v)) {
        return true;
    }
    return false;
}

bool Vec3::operator<=(const float &v) {
    if((x <= v) && (y <= v) && (z <= v)) {
        return true;
    }
    return false;
}

Vec3& Vec3::operator=(const Vec3 &v) {
    if(this != &v){
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }
    return *this;
}

Vec3 Vec3::operator*(const Vec3 &v) {
    return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3& Vec3::operator*=(const Vec3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vec3 Vec3::operator/(const Vec3 &v) {
    if(v.x != 0 && v.y != 0){
        return Vec3(x / v.x, y / v.y, z / v.z);
    }
    return *this;
}

Vec3& Vec3::operator/=(const Vec3 &v) {
   if(v.x != 0 && v.y != 0){
       x /= v.x;
       y /= v.y;
       z /= v.z;
   }
   return *this;
}

Vec3 Vec3::operator+(const Vec3 &v) {
   return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3& Vec3::operator+=(const Vec3 &v) {
   x += v.x;
   y += v.y;
   z += v.z;
   return *this;
}

Vec3 Vec3::operator-(const Vec3 &v) {
   return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3& Vec3::operator-=(const Vec3 &v) {
   x -= v.x;
   y -= v.y;
   z -= v.z;
   return *this;
}

bool Vec3::operator==(const Vec3 &v) {
    if((x == v.x) && (y == v.y) && (z == v.z)) {
        return true;
    }
    return false;
}

bool Vec3::operator>=(const Vec3 &v) {
    if((x >= v.x) && (y >= v.y) && (z >= v.z)) {
        return true;
    }
    return false;
}

bool Vec3::operator<=(const Vec3 &v) {
    if((x <= v.x) && (y <= v.y) && (z <= v.z)) {
        return true;
    }
    return false;
}