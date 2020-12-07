#include "GameCore.hpp"

using namespace projector;

GameCore::GameCore() {
    sAppName = "Blocks";
}

bool GameCore::OnUserCreate() {

    this->fov = 1.0f / std::tan( (90.0f * 0.5f) / (180.0f * PI) );
    this->aspectRatio = (float)ScreenWidth() / (float)ScreenHeight();
    this->zNear = 0.1f;
    this->zFar = 1000.0f;

    this->theta = 0.0f;

    this->camera = { 0.0f, 0.0f, 0.0f, 0.0f };

    this-> projectionMatrix = createProjectionMatrix(
        this->aspectRatio,
        this->fov,
        this->zNear,
        this->zFar
    );

    return true;
}

bool GameCore::OnUserUpdate(float fElapsedTime) {
    
    Clear(olc::DARK_BLUE);

    theta += 1.0f * fElapsedTime;
    vector4d translateVector = { 0.0f, 0.0f, 3.0f, 0.0f }; 
    matrix4d rotationMatrix = createXRotationMatrix(theta) * createZRotationMatrix(theta);

    for (triangle t : CUBE.triangles) {

        triangle translated, projected;

        // Projection
        for (size_t i{ 0 }; i < 3; ++i) {

            // Translation
            translated.points[i] = translatePoint(t.points[i], translateVector, rotationMatrix);

        }

        vector4d normal{ 0.0f, 0.0f, 0.0f, 0.0f };

        normal = getNormalOfTriangle(translated);
        normalize(normal);

        vector4d normalizedTrianglePoint{ 0.0f, 0.0f, 0.0f, 0.0f };
        normalizedTrianglePoint = (translated.points[0] - camera);

        //if (normal[2] < 0) {
        if (dotProduct(normal, normalizedTrianglePoint ) < 0.0f) {

            for (size_t i{ 0 }; i < 3; ++i) {

                // Projection
                
                projected.points[i] = projectPoint(translated.points[i], projectionMatrix);
            }

            // Scale temporary
            for (size_t i{ 0 }; i < 3; ++i) {

                projected.points[i][0] += 5.0f;
                projected.points[i][1] += 5.0f;

                projected.points[i][0] *= 0.05f * (float)ScreenWidth();
                projected.points[i][1] *= 0.05f * (float)ScreenHeight();
            }

            _DrawTriangle(projected, olc::WHITE);
        }
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