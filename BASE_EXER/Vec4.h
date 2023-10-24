#ifndef __VEC4__
#define __VEC4__

#include <cmath>

class Vec4 {
    private:
        float x;
        float y;
        float z;
        float w;
    public:
        Vec4();
        Vec4(const float &x,const float &y,const float &z, const float &w);
        Vec4(const float &xyzw);

        float getX();
        float getY();
        float getZ();
        float getW();

        void set(const float &x, const float &y, const float &z, const float &w);
        void setX(const float &x);
        void setY(const float &y);
        void setZ(const float &z);
        void setW(const float &w);

        float length();
        Vec4& normalized();
        Vec4& abs();
        float dot(const Vec4 &v);

        Vec4& operator=(const float &v);
        Vec4 operator*(const float &v);
        Vec4& operator*=(const float &v);
        Vec4 operator/(const float &v);
        Vec4& operator/=(const float &v);
        Vec4 operator+(const float &v);
        Vec4& operator+=(const float &v);
        Vec4 operator-(const float &v);
        Vec4& operator-=(const float &v);

        Vec4& operator=(const Vec4 &v);
        Vec4 operator*(const Vec4 &v);
        Vec4& operator*=(const Vec4 &v);
        Vec4 operator/(const Vec4 &v);
        Vec4& operator/=(const Vec4 &v);
        Vec4 operator+(const Vec4 &v);
        Vec4& operator+=(const Vec4 &v);
        Vec4 operator-(const Vec4 &v);
        Vec4& operator-=(const Vec4 &v);
};

#endif