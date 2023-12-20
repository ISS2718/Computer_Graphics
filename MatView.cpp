#include "MatView.h"

MatView::MatView() {
    view = new Mat4(true);
    rotation = new Mat4(true);
    translation = new Mat4(true);
    n = new Vec3();
    u = new Vec3();
    v = new Vec3();

    update = false;
}

MatView::MatView(Vec3 &eye_position, Vec3 &target, Vec3 &view_up) : MatView() {
    setViewCoordinates(eye_position, target, view_up);
}

MatView::~MatView() {
    delete view;
    delete rotation;
    delete translation;
    delete n;
    delete u;
    delete v;
}

GLfloat* MatView::getViewMatrix() {
    if(update) {
        updateViewMatrix();
    }

    return (GLfloat*) view->getMatrix();
}

void MatView::setViewCoordinates(Vec3 &eye_position, Vec3 &target, Vec3 &view_up) {
    *n = (eye_position - target);
    *n /= n->normalized();

    *u = view_up.cross(*n);
    *u /= u->normalized();

    *v = n->cross(*u);

    translation->setValuePosition(3, 0, eye_position.getX());
    translation->setValuePosition(3, 1, eye_position.getY());
    translation->setValuePosition(3, 2, eye_position.getZ());

    rotation->setValuePosition(0, 0, u->getX());
    rotation->setValuePosition(0, 1, u->getY());
    rotation->setValuePosition(0, 2, u->getZ());

    rotation->setValuePosition(1, 0, v->getX());
    rotation->setValuePosition(1, 1, v->getY());
    rotation->setValuePosition(1, 2, v->getZ());

    rotation->setValuePosition(2, 0, n->getX());
    rotation->setValuePosition(2, 1, n->getY());
    rotation->setValuePosition(2, 2, n->getZ());

    update = true;
}

void MatView::updateViewMatrix() {
    *view = ((*rotation) * (*translation));

    update = false;
}