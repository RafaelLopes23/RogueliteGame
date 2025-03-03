#ifndef PLAYER_H
#define PLAYER_H

#include "entities/Entity.h"
#include <SDL3/SDL.h>

class Player : public Entity {
public:
    Player(float x, float y);
    ~Player() override;
    
    void update() override;
    void render() override;
    
    void handleInput(const bool* keyState);

	bool isAttacking() const { return attacking; }
	int getAttackDamage() const { return attackDamage; }
	int getFacingDirection() const { return facingDirection; } // 0= right, 1=down, 2=left, 3=up

	void attack();
    
private:
    float speed;
    bool attacking;
	int attackDamage;
    int attackCooldown;
	int attackCooldownMax;
	int facingDirection;  // 0= right, 1=down, 2=left, 3=up
};

#endif // PLAYER_H