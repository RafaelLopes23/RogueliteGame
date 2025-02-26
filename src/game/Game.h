#ifndef GAME_H
#define GAME_H

#include <string>
#include "rendering/Renderer.h"
#include "entities/Player.h"

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
    
    void processInput();
    void update();
    void render();
};

#endif // GAME_H