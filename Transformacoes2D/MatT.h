#ifndef __MAT_Transformation__
#define __MAT_Transformation__

#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
#include "Mat4.h"

class MatT
{
    private:
        Mat4* transformation;
        Mat4* translation;
        Mat4* rotation;
        Mat4* scale;

        bool update; 

        void updateTransformationMatrix();
    public:
        MatT();
        ~MatT();

        GLfloat* getTranformationMatrix();
        void setRotationX(const float &r);
        void setRotationY(const float &r);
        void setRotationZ(const float &r);
        void setTranslation(const float &x, const float &y, const float &z);
        void setScale(const float &s);
        void setScale(const float &x, const float &y, const float &z);
};

#endif