#include "Vec2.h"

Vec2::Vec2() {}

Vec2::Vec2(const float &x,const float &y) : x(x), y(y) {}

Vec2::Vec2(const float &xy) : x(xy), y(xy) {}

float Vec2::getX() {
    return x;
}

float Vec2::getY() {
    return y;
}

void Vec2::set(const float &x, const float &y) {
    this->x = x;
    this->y = y;
}

void Vec2::setX(const float &x) {
    this->x = x;
}

void Vec2::setY(const float &y) {
    this->y = y;
}

float Vec2::length() {
    return (float) sqrt(x*x + y*y);
}

Vec2& Vec2::normalized() {
    float len = length();
    if(len != 0) {
        x /= len;
        y /= len;
    }
    return *this;
}

Vec2& Vec2::abs() {
    x = (float) fabs(x);
    y = (float) fabs(y);
    return *this;
}

float Vec2::dot(const Vec2 &v) {
    return x * v.x + y * v.y;
}

float Vec2::cross(const Vec2& v) {
    return (float)(x * v.y - y * v.x);
}

Vec2& Vec2::operator=(const float &v) {
    this->x = v;
    this->y = v;
    return *this;
}

Vec2 Vec2::operator*(const float &v) {
    return Vec2(x * v, y * v);
}

Vec2& Vec2::operator*=(const float &v) {
    x *= v;
    y *= v;
    return *this;
}

Vec2 Vec2::operator/(const float &v) {
    if(v != 0) {
        return Vec2(x / v, y / v);
    }
    return *this;
}

Vec2& Vec2::operator/=(const float &v) {
    if(v != 0) {
        x /= v;
        y /= v;
    }
    return *this;
}

Vec2 Vec2::operator+(const float &v) {
    return Vec2(x + v, y + v);
}

Vec2& Vec2::operator+=(const float &v) {
    x += v;
    y += v;
    return *this;
}

Vec2 Vec2::operator-(const float &v) {
    return Vec2(x - v, y - v);
}

Vec2& Vec2::operator-=(const float &v) {
    x -= v;
    y -= v;
    return *this;
}


Vec2& Vec2::operator=(const Vec2 &v) {
    if(this != &v){
        this->x = v.x;
        this->y = v.y;
    }
    return *this;
}

Vec2 Vec2::operator*(const Vec2 &v) {
    return Vec2(x * v.x, y * v.y);
}

Vec2& Vec2::operator*=(const Vec2 &v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

Vec2 Vec2::operator/(const Vec2 &v) {
    if(v.x != 0 && v.y != 0){
    return Vec2(x / v.x, y / v.y);
    }
    return *this;
}

Vec2& Vec2::operator/=(const Vec2 &v) {
   if(v.x != 0 && v.y != 0){
       x /= v.x;
       y /= v.y;
   }
   return *this;
}

Vec2 Vec2::operator+(const Vec2 &v) {
   return Vec2(x + v.x, y + v.y);
}

Vec2& Vec2::operator+=(const Vec2 &v) {
   x += v.x;
   y += v.y;
   return *this;
}

Vec2 Vec2::operator-(const Vec2 &v) {
   return Vec2(x - v.x, y - v.y);
}

Vec2& Vec2::operator-=(const Vec2 &v) {
   x -= v.x;
   y -= v.y;
   return *this;
}