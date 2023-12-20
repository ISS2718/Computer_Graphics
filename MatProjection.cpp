#include "MatProjection.h"

MatProjection::MatProjection() {
    perspective = new Mat4(true);
    update = false;
}

MatProjection::MatProjection(float &aspect, float &fovy, float &z_near, float &z_far) : MatProjection() {
    setPerspectiveParameters(aspect, fovy, z_near, z_far);
}

MatProjection::~MatProjection() {
    delete perspective;
}

GLfloat* MatProjection::getProjectionMatrix() {
    if(update) {
        updatePerspectiveMatrix();
    }

    return (GLfloat*) perspective->getMatrix();
}

void MatProjection::setPerspectiveParameters(float &aspect, float &fovy, float &z_near, float &z_far) {
    this->aspect = aspect;
    this->fovy = fovy;
    this->z_near = z_near;
    this->z_far = z_far;

    update = true;
}


void MatProjection::updatePerspectiveMatrix() {
    float tan_half_fovy = tan(fovy/2);
    perspective->setValuePosition(0, 0, (1) / (tan_half_fovy * aspect));
    perspective->setValuePosition(1, 1, (1) / (tan_half_fovy));
    perspective->setValuePosition(2, 2, -(z_far + z_near) / (z_far - z_near));
    perspective->setValuePosition(2, 3, -(1));
    perspective->setValuePosition(3, 2, -(2 * z_far * z_near) / (z_far - z_near));

    update = false;
}