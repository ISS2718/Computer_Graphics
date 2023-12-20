#ifndef __CAMERA__
#define __CAMERA__

#include "MatProjection.h"
#include "MatView.h"
#include "Vec3.h"

class Camera {
private:
    MatProjection perspective;
    MatView view;

    Vec3 camera_coordinates;
    Vec3 camera_target;
    Vec3 cemera_view_up;


public:
    Camera();
    ~Camera();
};
#endif