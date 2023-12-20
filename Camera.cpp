#include "Camera.h"

Camera::Camera() {
    perspective = new MatProjection();
    view = new MatView();
    camera_coordinates = new Vec3(0);
    camera_target = new Vec3(0);
    camera_view_up = new Vec3(0);

    update_view = false;
}

Camera::~Camera() {
    delete perspective;
    delete view;
    delete camera_coordinates;
    delete camera_target;
    delete camera_view_up;
}

GLfloat* Camera::getMatPerspective() {
    return perspective->getProjectionMatrix();
}

GLfloat* Camera::getMatView(){
    if(update_view) {
        view->setViewCoordinates(*camera_coordinates, *camera_target, *camera_view_up);
    }
    return view->getViewMatrix();
}

Vec3 Camera::getCameraCoordinates(){
    return *camera_coordinates;
}

float Camera::getCameraCoordinateX(){
    return camera_coordinates->getX();
}

float Camera::getCameraCoordinateY(){
    return camera_coordinates->getY();
}

float Camera::getCameraCoordinateZ(){
    return camera_coordinates->getZ();
}

Vec3 Camera::getCameraTarget(){
    return *camera_target;
}

float Camera::getCameraTargetX(){
    return camera_target->getX();
}

float Camera::getCameraTargetY(){
    return camera_target->getY();
}

float Camera::getCameraTargetZ(){
    return camera_target->getZ();
}

void Camera::setCameraCoordinates(const float &x,const float &y, const float &z){
    camera_coordinates->set(x, y, z);
    
    update_view = true;
}

void Camera::setCameraCoordinateX(const float &x){
    camera_coordinates->setX(x);
    
    update_view = true;
}

void Camera::setCameraCoordinateY(const float &y){
    camera_coordinates->setY(y);

    update_view = true;
}

void Camera::setCameraCoordinateZ(const float &z){
    camera_coordinates->setZ(z);

    update_view = true;
}

void Camera::setCameraTarget(const float &x,const float &y, const float &z){
    camera_target->set(x, y, z);

    update_view = true;
}

void Camera::setCameraTargetX(const float &x){
    camera_target->setX(x);

    update_view = true;
}
void Camera::setCameraTargetY(const float &y){
    camera_target->setY(y);

    update_view = true;
}

void Camera::setCameraTargetZ(const float &z){
    camera_target->setZ(z);

    update_view = true;
}

void Camera::setCameraViewUp(const float &x,const float &y, const float &z) {
    camera_view_up->set(x, y, z);

    update_view = true;
}

void Camera::setZNear(const float &z_near){
    perspective->setZNear(z_near);
}
void Camera::setZFar(const float &z_far){
    perspective->setZFar(z_far);
}

void Camera::setFovy(const float &fovy){
    perspective->setFovy(fovy);
}

void Camera::setWindowAspect(const float &window_aspect){
    perspective->setAspect(window_aspect);
}