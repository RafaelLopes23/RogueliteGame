#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize(const std::string& title, int width, int height);
    void clear();
    void present();
    void cleanup();
    
    // Rendering methods
    void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    SDL_Renderer* getSDLRenderer() const { return renderer; }
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
};

#endif // RENDERER_H