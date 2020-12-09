#include "assets/Player.hpp"

void Player::onCreate() {
    this->playerCamera = Camera();
    this->setCameraRelativePosition( { .0f, 1.0f, .0f, 1.0f } );
    this->fov = 1.0f / std::tan( 90.0f / (360.0f * projector::PI) );
}

void Player::onUpdate(float deltaTime) {
    
}