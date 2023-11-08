#include "MatT.h"

MatT::MatT() {
    transformation = new Mat4(true);
    translation =  new Mat4(true);
    rotationX =  new Mat4(true);
    rotationY =  new Mat4(true);
    rotationZ =  new Mat4(true);
    scale = new Mat4(true);

    update = false;
}

MatT::~MatT() {
    delete transformation;
    delete translation;
    delete rotationX;
    delete rotationY;
    delete rotationZ;
    delete scale;
}

GLfloat* MatT::getTransformationMatrix() {
    if(update) {
        updateTransformationMatrix();
    }

    return (GLfloat*) transformation->getMatrix();
}

void MatT::setRotation(const float &rx, const float &ry, const float &rz) {
    setRotationX(rx);
    setRotationY(ry);
    setRotationZ(rz);
}

void MatT::setRotationX(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    rotationX->setValuePosition(1, 1, c);
    rotationX->setValuePosition(1, 2, -s);
    rotationX->setValuePosition(2, 1, s);
    rotationX->setValuePosition(2, 2, c);

    update = true;
}

void MatT::setRotationY(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    rotationY->setValuePosition(0, 0, c);
    rotationY->setValuePosition(0, 2, s);
    rotationY->setValuePosition(2, 0, -s);
    rotationY->setValuePosition(2, 2, c);

    update = true;
}

void MatT::setRotationZ(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    rotationZ->setValuePosition(0, 0, c);
    rotationZ->setValuePosition(0, 1, -s);
    rotationZ->setValuePosition(1, 0, s);
    rotationZ->setValuePosition(1, 1, c);

    update = true;
}

void MatT::setTranslation(const float &x, const float &y, const float &z) {
    translation->setValuePosition(0, 3, x);
    translation->setValuePosition(1, 3, y);
    translation->setValuePosition(2, 3, z);

    update = true;
}

void MatT::setTranslationX(const float &x){
    translation->setValuePosition(0, 3, x);
    update = true;
}

void MatT::setTranslationY(const float &y){
    translation->setValuePosition(1, 3, y);
    update = true;
}

void MatT::setTranslationZ(const float &z){
    translation->setValuePosition(2, 3, z);
    update = true;
}


void MatT::setScale(const float &s) {
    scale->setValuePosition(0, 0, s);
    scale->setValuePosition(1, 1, s);
    scale->setValuePosition(2, 2, s);

    update = true;
}

void MatT::setScale(const float &sx, const float &sy, const float &sz) {
    scale->setValuePosition(0, 0, sx);
    scale->setValuePosition(1, 1, sy);
    scale->setValuePosition(2, 2, sz);

    update = true;
}

void MatT::updateTransformationMatrix() {
    *transformation = ((*translation)  * (((*rotationZ) * (*rotationX)) * (*rotationY))) * (*scale);
}
