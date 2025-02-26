#include "entities/Player.h"
#include <SDL2/SDL.h>

Player::Player(float x, float y) 
    : Entity(x, y, "Player"), speed(5.0f) {
}

Player::~Player() {
}

void Player::update() {
    // Player-specific update logic
}

void Player::render() {
    // Player-specific render logic - will be implemented when we have a renderer
}

void Player::handleInput(const Uint8* keyState) {
    if (keyState[SDL_SCANCODE_W]) {
        y -= speed;
    }
    if (keyState[SDL_SCANCODE_S]) {
        y += speed;
    }
    if (keyState[SDL_SCANCODE_A]) {
        x -= speed;
    }
    if (keyState[SDL_SCANCODE_D]) {
        x += speed;
    }
}