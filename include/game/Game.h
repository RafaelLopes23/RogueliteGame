#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "rendering/Renderer.h"
#include "entities/Player.h"
#include "entities/Enemy.h"

class Game {
public:
    Game();
    ~Game();
    
    bool initialize();
    void run();
    void cleanup();
    
private:
    bool isRunning;
    unsigned int frameRate;
    std::string title;
    Renderer renderer;
    Player* player;
	std::vector<Enemy*> enemies;
    
    void processInput();
    void update();
    void render();
	void spawnEnemy();
	void checkCollisions();
    void renderAttackEffect();
};

#endif // GAME_H