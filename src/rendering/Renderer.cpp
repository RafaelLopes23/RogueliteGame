#include "rendering/Renderer.h"
#include <iostream>
#include <SDL3/SDL.h>

Renderer::Renderer() 
    : window(nullptr), renderer(nullptr), screenWidth(800), screenHeight(600) {
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize(const std::string& title, int width, int height) {
    screenWidth = width;
    screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        screenWidth,
        screenHeight,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    
    renderer = SDL_CreateRenderer(window, "opengl");

    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    return true;
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    SDL_Quit();
}

void Renderer::drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // Use SDL_FRect em vez de SDL_Rect
    SDL_FRect frect = { (float)x, (float)y, (float)width, (float)height };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &frect);
}