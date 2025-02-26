#ifndef PLAYER_H
#define PLAYER_H

#include "entities/Entity.h"
#include <SDL2/SDL.h>

class Player : public Entity {
public:
    Player(float x, float y);
    ~Player() override;
    
    void update() override;
    void render() override;
    
    void handleInput(const Uint8* keyState);
    
private:
    float speed;
};

#endif // PLAYER_H