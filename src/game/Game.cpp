#include "game/Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL3/SDL.h>
#include <cmath>

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

    //spawn one enemy
    spawnEnemy();
    
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
        if (e.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
    
    // Handle player input
    const bool* keyState = SDL_GetKeyboardState(NULL);
    player->handleInput(keyState);
}

void Game::update() {
    // Update game state
    player->update();

	// Update enemies
    for (auto* enemy : enemies) {
		if (enemy->isActive()) {
			enemy->update();
		}
    }

	// Check for collisions
	checkCollisions();
}

void Game::render() {
    // Clear the screen
    renderer.clear();
    
    // Render player
    renderer.drawRect(
        static_cast<int>(player->getX()),
        static_cast<int>(player->getY()),
        static_cast<int>(player->getWidth()),
        static_cast<int>(player->getHeight()),
        255, 0, 0, 255); // Red for player

	// Render enemies
    for (auto* enemy : enemies) {
        if (enemy->isActive()) {
            renderer.drawRect(
                static_cast<int>(enemy->getX()),
                static_cast<int>(enemy->getY()),
                static_cast<int>(enemy->getWidth()),
                static_cast<int>(enemy->getHeight()),
                255, 255, 255, 255); // White for enemies
        }
    }

	// Render attack effect if player is attacking
	if (player->isAttacking()) {
		renderAttackEffect();
	}

    
    // Present rendered content
    renderer.present();
}

void Game::spawnEnemy() {
    // Create enemy at a random position
    float enemyX = rand() % 700 + 50;
    float enemyY = rand() % 500 + 50;

    Enemy* enemy = new Enemy(enemyX, enemyY);
    enemies.push_back(enemy);
}

void Game::checkCollisions() {
    // check attack collision
    if (player->isAttacking()) {
        // set attack area based on player facing direction
        float attackX = player->getX();
        float attackY = player->getY();
        float attackWidth = 40;
        float attackHeight = 40;

        // Adjust attack area based on player facing direction
        switch (player->getFacingDirection()) {
        case 0: // right
            attackX = player->getX() + player->getWidth();
            attackHeight = player->getHeight();
            break;
        case 1: // down
            attackY = player->getY() + player->getHeight();
            attackWidth = player->getWidth();
            break;
        case 2: // left
            attackX = player->getX() - attackWidth;
            attackHeight = player->getHeight();
            break;
        case 3: // up
            attackY = player->getY() - attackHeight;
            attackWidth = player->getWidth();
            break;
        }
        // Area attack entity
        Entity attackArea(attackX, attackY, "AttackArea");

        // Check for collision with enemies
        for (auto* enemy : enemies) {
            if (enemy->isActive() && attackArea.checkCollision(enemy)) {
                // Enemy hit by player attack
                enemy->setActive(false);
            }
        }
    }
}

void Game::renderAttackEffect() {
	//Render attack effect based on player facing direction
	float attackX = player->getX();
	float attackY = player->getY();
	float attackWidth = 40;
	float attackHeight = 40;

    // adjust attack area based on direction
    switch (player->getFacingDirection()) {
    case 0: // right
        attackX = player->getX() + player->getWidth();
        attackHeight = player->getHeight();
        attackWidth = 20;
        break;
    case 1: // down
        attackY = player->getY() + player->getHeight();
        attackWidth = player->getWidth();
        attackHeight = 20;
        break;
    case 2: // left
        attackX = player->getX() - attackWidth;
        attackHeight = player->getHeight();
        attackWidth = 20;
        break;
    case 3: // up
        attackY = player->getY() - attackHeight;
        attackWidth = player->getWidth();
        attackHeight = 20;
        break;
    }

	//render attack effect (semi transparent rectangle)
	renderer.drawRect(
		static_cast<int>(attackX),
		static_cast<int>(attackY),
		attackWidth,
		attackHeight,
		200, 200, 0, 128);

}