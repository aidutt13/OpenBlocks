#ifndef ASSET_PLAYER_H
#define ASSET_PLAYER_H

#include "Object.hpp"
#include "assets/Camera.hpp"

#include "Projector.hpp"


class Player : public object::Object {

public:
    float fov;

    Camera playerCamera;
    projector::vector4d cameraRelativePosition;

public:

    /*
    *   Constructor
    */ 
    Player() {};

    projector::vector4d getCameraRelativePosition() {
        return this->cameraRelativePosition;
    }

    void setCameraRelativePosition(projector::vector4d v) {
        this->cameraRelativePosition = v;
        auto newPos = v + this->getWorldPosition();
        this->playerCamera.setWorldPosition(
            newPos
        );
    }

    void onCreate() override;

    void onUpdate(float) override;
};

#endif