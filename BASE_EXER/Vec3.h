#ifndef __VEC3__
#define __VEC3__

#include <cmath>

class Vec3 {
    private:
        float x;
        float y;
        float z;
    public:
        Vec3();
        Vec3(const float &x,const float &y,const float &z);
        Vec3(const float &xyz);

        float getX();
        float getY();
        float getZ();

        void set(const float &x, const float &y, const float &z);
        void setX(const float &x);
        void setY(const float &y);
        void setZ(const float &z);

        float length();
        Vec3& normalized();
        Vec3& abs();
        float dot(const Vec3 &v);
        Vec3 cross(const Vec3& v);

        Vec3& operator=(const float &v);
        Vec3 operator*(const float &v);
        Vec3& operator*=(const float &v);
        Vec3 operator/(const float &v);
        Vec3& operator/=(const float &v);
        Vec3 operator+(const float &v);
        Vec3& operator+=(const float &v);
        Vec3 operator-(const float &v);
        Vec3& operator-=(const float &v);

        bool operator==(const float &v);
        bool operator>=(const float &v);
        bool operator<=(const float &v);

        Vec3& operator=(const Vec3 &v);
        Vec3 operator*(const Vec3 &v);
        Vec3& operator*=(const Vec3 &v);
        Vec3 operator/(const Vec3 &v);
        Vec3& operator/=(const Vec3 &v);
        Vec3 operator+(const Vec3 &v);
        Vec3& operator+=(const Vec3 &v);
        Vec3 operator-(const Vec3 &v);
        Vec3& operator-=(const Vec3 &v);

        bool operator==(const Vec3 &v);
        bool operator>=(const Vec3 &v);
        bool operator<=(const Vec3 &v);
};

#endif