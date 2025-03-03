#include "entities/Player.h"
#include <SDL3/SDL.h>

Player::Player(float x, float y) 
    : Entity(x, y, "Player"), speed(5.0f), attacking(false),
      attackDamage(10), attackCooldown(0), attackCooldownMax(20), facingDirection(0) {
    width = 32;
	height = 32;
}

Player::~Player() {
}

void Player::update() {
    // reduce attack cooldown if active
    if (attackCooldown > 0) {
        attackCooldown--;
    } else {
		attacking = false;
    }
}

void Player::render() {
    // Player-specific render logic - will be implemented when we have a renderer
}

void Player::handleInput(const bool* keyState) {
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

	if (keyState[SDL_SCANCODE_SPACE] && attackCooldown <= 0) {
		attack();
	}
}

void Player::attack() {
	if (attackCooldown <= 0) {
		attacking = true;
		attackCooldown = attackCooldownMax;
	}
}