#ifndef GAMECORE_H
#define GAMECORE_H

#include "PixelGameEngine.hpp"

#include "Projector.hpp"

#include <iostream>

class GameCore;

class GameCore : public olc::PixelGameEngine {
    
public:
    float fov = .0f;
    float aspectRatio = .0f;
    float zNear = .0f;
    float zFar = .0f;

    float thetaX = .0f;
    float thetaY = .0f;
    float thetaZ = .0f;

    projector::vector4d camera;

    projector::matrix4d projectionMatrix;

public:
    /*
    *   Constructor
    */
    GameCore();


public:
    /*
    *   Method called at the start of the core
    */
    bool OnUserCreate() override;

    /*
    *   Main loop
    */
    bool OnUserUpdate(float) override;

protected:

    void _DrawTriangle(projector::triangle&, const olc::Pixel&);
    void _FillTriangle(projector::triangle&, const olc::Pixel&);
};


#endif