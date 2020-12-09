#ifndef GAMECORE_H
#define GAMECORE_H

#include "PixelGameEngine.hpp"

#include "Projector.hpp"

#include "Object.hpp"

#include "assets/Player.hpp"

#include <iostream>

class GameCore;

class GameCore : public olc::PixelGameEngine {
    
public:
    Player player;

    projector::projection_variables vars = {.0f, .0f, .0f, .0f, { .0f, .0f, .0f, .0f} };

    object::Object cube;

    float thetaX = .0f;
    float thetaY = .0f;
    float thetaZ = .0f;

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