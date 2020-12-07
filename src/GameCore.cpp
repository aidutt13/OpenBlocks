#include "GameCore.hpp"

using namespace projector;

GameCore::GameCore() {
    sAppName = "Blocks";
}

bool GameCore::OnUserCreate() {

    this->fov = 1.0 / std::tan(90.0 / 360.0 * projector::PI);
    this->aspectRatio = ScreenWidth() / ScreenHeight();
    this->zNear = 1.0;
    this->zFar = 1000.0;


    return true;
}

bool GameCore::OnUserUpdate(float fElapsedTime) {
    
    std::cout << "Hello World\n";
    Clear(olc::BLACK);

    for (triangle t : CUBE.triangles) {
        triangle projected;
        std::cout << "loop\n";
        for (size_t i{ 0 }; i < 3; ++i) {
            projected.points[i] = projectPoint(t.points[i], projectionMatrix);
        }
        
        auto& points = projected.points;


        DrawLine(
            points[0].round(0), points[0].round(1),
            points[1].round(0), points[1].round(1)
        );
        DrawLine(
            points[0].round(0), points[0].round(1),
            points[2].round(0), points[2].round(1)
        );
        DrawLine(
            points[1].round(0), points[1].round(1),
            points[2].round(0), points[2].round(1)
        );
        
    }

    return true;
}

void GameCore::_DrawTriangle(triangle& tri, const olc::Pixel& p = olc::WHITE) {
    auto& points = tri.points;
    
    DrawTriangle(
        points[0].round(0), points[0].round(1),
        points[1].round(0), points[1].round(1),
        points[2].round(0), points[2].round(1),
        p
    );
}