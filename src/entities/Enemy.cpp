#include "entities/Enemy.h"
#include <cmath>

Enemy::Enemy(float x, float y)
    : Entity(x, y, "Enemy"), active(true), moveSpeed(2.0f) {
    // Tamanho menor para o inimigo
    width = 16;
    height = 16;
}

Enemy::~Enemy() {
}

void Enemy::update() {
    // L�gica b�sica de movimento do inimigo
    // No futuro, pode-se implementar IA para perseguir o jogador
}

void Enemy::render() {
    // A renderiza��o ser� feita na classe Game
}