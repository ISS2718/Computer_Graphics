#ifndef __MAT_Transformation__
#define __MAT_Transformation__

#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

#include "Mat4.h"

class MatT
{
    private:
        Mat4* transformation;
        Mat4* translation;
        Mat4* rotationX;
        Mat4* rotationY;
        Mat4* rotationZ;
        Mat4* scale;

        bool update; 

        void updateTransformationMatrix();
    public:
        MatT();
        ~MatT();

        GLfloat* getTransformationMatrix();
        void setRotationX(const float &r);
        void setRotationY(const float &r);
        void setRotationZ(const float &r);
        void setTranslation(const float &x, const float &y, const float &z);
        void setScale(const float &s);
        void setScale(const float &x, const float &y, const float &z);
};

#endif