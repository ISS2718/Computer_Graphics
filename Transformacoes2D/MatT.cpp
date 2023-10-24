#include "MatT.h"

MatT::MatT() {
    transformation = new Mat4(true);
    translation =  new Mat4(true);
    rotation = new Mat4(true);
    scale = new Mat4(true);

    update = false;
}

MatT::~MatT() {
    delete transformation;
    delete translation;
    delete rotation;
    delete scale;
}

GLfloat* MatT::getTranformationMatrix() {
    if(update) {
        updateTransformationMatrix();
    }

    return (GLfloat*) transformation->getMatix();
}

void MatT::setRotationX(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    translation->setValuePosition(1, 1, c);
    translation->setValuePosition(1, 2, -s);
    translation->setValuePosition(2, 1, s);
    translation->setValuePosition(2, 2, c);

    update = true;
}

void MatT::setRotationY(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    translation->setValuePosition(0, 0, c);
    translation->setValuePosition(0, 2, s);
    translation->setValuePosition(2, 0, -s);
    translation->setValuePosition(2, 2, c);

    update = true;
}

void MatT::setRotationZ(const float &r) {
    float s = (float) sin(r);
    float c = (float) cos(r);

    translation->setValuePosition(0, 0, c);
    translation->setValuePosition(0, 1, -s);
    translation->setValuePosition(1, 0, s);
    translation->setValuePosition(1, 1, c);

    update = true;
}

void MatT::setTranslation(const float &x, const float &y, const float &z) {
    translation->setValuePosition(0, 3, x);
    translation->setValuePosition(1, 3, y);
    translation->setValuePosition(2, 3, z);

    update = true;
}

void MatT::setScale(const float &s) {
    scale->setValuePosition(0, 0, s);
    scale->setValuePosition(1, 1, s);
    scale->setValuePosition(2, 2, s);

    update = true;
}

void MatT::setScale(const float &x, const float &y, const float &z) {
    scale->setValuePosition(0, 0, x);
    scale->setValuePosition(1, 1, y);
    scale->setValuePosition(2, 2, z);

    update = true;
}

void MatT::updateTransformationMatrix() {
    *transformation = ((*translation) * (*rotation)) * (*scale);
}
