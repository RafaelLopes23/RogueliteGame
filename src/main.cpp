#include <iostream>
#include "game/Game.h"

int main() {
    std::cout << "Starting Roguelite Game..." << std::endl;
    
    Game game;
    game.initialize();
    game.run();
    game.cleanup();
    
    return 0;
}