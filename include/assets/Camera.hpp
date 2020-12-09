#ifndef ASSET_CAMERA_H
#define ASSET_CAMERA_H

#include "Object.hpp"

class Camera : public object::Object {

public:

    float fov;

public:

    /*
    *   Constructor
    */ 
    Camera() {};

};

#endif