#ifndef ENEMY_H
#define ENEMY_H

#include "entities/Entity.h"

class Enemy : public Entity {
public:
    Enemy(float x, float y);
    ~Enemy() override;

    void update() override;
    void render() override;

    bool isActive() const { return active; }
    void setActive(bool state) { active = state; }

private:
    bool active;
    float moveSpeed;
};

#endif // ENEMY_H