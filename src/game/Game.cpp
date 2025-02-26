#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

Game::Game() : isRunning(false), frameRate(60), title("Roguelite Game"), player(nullptr) {
    // Constructor
}

Game::~Game() {
    // Destructor
    if (player) {
        delete player;
    }
}

bool Game::initialize() {
    std::cout << "Initializing game..." << std::endl;
    
    // Initialize renderer
    if (!renderer.initialize(title, 800, 600)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return false;
    }
    
    // Create player
    player = new Player(400, 300);
    
    isRunning = true;
    return true;
}

void Game::run() {
    std::cout << "Game is running!" << std::endl;
    
    // Game loop
    while(isRunning) {
        auto frameStart = std::chrono::high_resolution_clock::now();
        
        processInput();
        update();
        render();
        
        // Simple frame rate control
        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        auto frameTime = 1000 / frameRate; // time per frame in milliseconds
        
        if(frameDuration.count() < frameTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - frameDuration.count()));
        }
    }
}

void Game::cleanup() {
    std::cout << "Cleaning up game resources..." << std::endl;
    renderer.cleanup();
}

void Game::processInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
        }
    }
    
    // Handle player input
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    player->handleInput(keyState);
}

void Game::update() {
    // Update game state
    player->update();
}

void Game::render() {
    // Clear the screen
    renderer.clear();
    
    // Render player
    renderer.drawRect(
        static_cast<int>(player->getX()),
        static_cast<int>(player->getY()),
        32, 32, 255, 0, 0, 255); // Red square for player
    
    // Present rendered content
    renderer.present();
}