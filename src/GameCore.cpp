#include "GameCore.hpp"

using namespace projector;

GameCore::GameCore() {
    sAppName = "Blocks";
}

bool GameCore::OnUserCreate() {

    this->thetaX = 0.0f;
    this->thetaY = 0.0f;
    this->thetaZ = 0.0f;

    this->player.onCreate();

    this->vars.aspectRatio = (float)ScreenWidth() / (float)ScreenHeight();
    this->vars.fov = this->player.fov;
    this->vars.zNear = 0.1f;
    this->vars.zFar = 1000.0f;
    this->vars.camera_pos = this->player.getWorldPosition() + this->player.cameraRelativePosition;

    this->cube.setObjectMesh(projector::CUBE);

    return true;
}

bool GameCore::OnUserUpdate(float deltaTime) {
    
    Clear(olc::DARK_BLUE);

    this->player.onUpdate(deltaTime);

    mesh m = projectObjectToScreen(&this->cube, this->vars);
  
    for (triangle& t : m.triangles)
        _FillTriangle(t, olc::WHITE);

    return true;
}

void GameCore::_DrawTriangle(triangle& tri, const olc::Pixel& p) {
    auto& points = tri.points;
    
    DrawTriangle(
        points[0].round(0), points[0].round(1),
        points[1].round(0), points[1].round(1),
        points[2].round(0), points[2].round(1),
        p
    );
}

void GameCore::_FillTriangle(triangle& tri, const olc::Pixel& p) {
    auto& points = tri.points;
    
    FillTriangle(
        points[0].round(0), points[0].round(1),
        points[1].round(0), points[1].round(1),
        points[2].round(0), points[2].round(1),
        p
    );
}