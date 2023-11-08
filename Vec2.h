#ifndef __VEC2__
#define __VEC2__

#include <cmath>

class Vec2 {
    private:
        float x;
        float y;
    public:
        Vec2();
        Vec2(const float &x,const float &y);
        Vec2(const float &xy);

        float getX();
        float getY();

        void set(const float &x, const float &y);
        void setX(const float &x);
        void setY(const float &y);

        float length();
        Vec2& normalized();
        Vec2& abs();
        float dot(const Vec2 &v);
        float cross(const Vec2 &v);

        Vec2& operator=(const float &v);
        Vec2 operator*(const float &v);
        Vec2& operator*=(const float &v);
        Vec2 operator/(const float &v);
        Vec2& operator/=(const float &v);
        Vec2 operator+(const float &v);
        Vec2& operator+=(const float &v);
        Vec2 operator-(const float &v);
        Vec2& operator-=(const float &v);

        Vec2& operator=(const Vec2 &v);
        Vec2 operator*(const Vec2 &v);
        Vec2& operator*=(const Vec2 &v);
        Vec2 operator/(const Vec2 &v);
        Vec2& operator/=(const Vec2 &v);
        Vec2 operator+(const Vec2 &v);
        Vec2& operator+=(const Vec2 &v);
        Vec2 operator-(const Vec2 &v);
        Vec2& operator-=(const Vec2 &v);
};

#endif