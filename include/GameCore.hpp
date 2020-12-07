#ifndef GAMECORE_H
#define GAMECORE_H

#include "PixelGameEngine.hpp"

#include "Projector.hpp"

#include <iostream>

class GameCore;

class GameCore : public olc::PixelGameEngine {
    
public:
    double fov = .0;
    double aspectRatio = .0;
    double zNear = .0;
    double zFar = .0;

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
};


#endif