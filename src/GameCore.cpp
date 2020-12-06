#include "GameCore.hpp"

using namespace projector;

GameCore::GameCore() {
    sAppName = "Blocks";
}

bool GameCore::OnUserCreate() {

    this->fov = 1.0 / std::tan(90.0 / 360.0 * projector::PI);
    this->aspectRatio = ScreenWidth() / ScreenHeight();
    this->zNear = 0.1;
    this->zFar = 1000.0;


    return true;
}

bool GameCore::OnUserUpdate(float fElapsedTime) {
    
    std::cout << "Hello World\n";
    Clear(olc::BLACK);

    for (triangle t : CUBE.triangles) {
        triangle projected;

        for (size_t i{ 0 }; i < 3; ++i) {
            projected.points[i] = projectPoint(t.points[i], projectionMatrix);
        }

        _DrawTriangle(projected, olc::WHITE);
    }

    return true;
}

void GameCore::_DrawTriangle(const triangle& tri, const olc::Pixel& p = olc::WHITE) {
    olc::vi2d v[3];
    const auto& points = tri.points;
    for (size_t i = 0; i < 3; ++i) {
        v[i] = {
            static_cast<int>(std::round(points[i][0])),     // X
            static_cast<int>(std::round(points[i][1]))      // Y
        };
    }

    DrawTriangle(v[0], v[1], v[2], p);
}