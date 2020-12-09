#ifndef OBJECT_H
#define OBJECT_H

#include "Projector.hpp"

namespace object {

/*
*   Class that represents any object in the world
*/
class Object;

/*
*   Class that represents any object in the world
*/
class Object {

protected:

    projector::mesh objectMesh;
    projector::vector4d worldPosition;
    projector::vector4d worldRotation;
    projector::vector4d worldScale;

    projector::matrix4d rotationMatrix;
    projector::matrix4d scaleMatrix;

public:

    /*
    *   Constructor
    */ 
    Object();

public:

    projector::mesh getObjectMesh() {
        return this->objectMesh;
    }

    void setObjectMesh(projector::mesh m) {
        this->objectMesh = m;
    }

    projector::vector4d getWorldPosition() {
        return this->worldPosition;
    }

    void setWorldPosition(projector::vector4d& v) {
        this->worldPosition = v;
    }

    projector::vector4d getWorldRotation() {
        return this->worldRotation;
    }

    void setWorldRotation(projector::vector4d& v) {
        this->worldRotation = v;

        this->rotationMatrix =
            projector::createXRotationMatrix(v[0]) *
            projector::createYRotationMatrix(v[1]) *
            projector::createZRotationMatrix(v[2]);
    }

    projector::vector4d getWorldScale() {
        return this->worldScale;
    }

    void setWorldScale(projector::vector4d& v) {
        this->worldScale = v;

        this->scaleMatrix.fillAll(0.0f);

        this->scaleMatrix[0][0] = v.at(0);
        this->scaleMatrix[1][1] = v.at(1);
        this->scaleMatrix[2][2] = v.at(2);

        this->scaleMatrix[3][3] = 1.0f;
    }

    projector::matrix4d getRotationMatrix() {
        return this->rotationMatrix;
    }

    projector::matrix4d getScaleMatrix() {
        return this->scaleMatrix;
    }

public:

    virtual void onCreate();

    virtual void onUpdate(float);
};

}

#endif