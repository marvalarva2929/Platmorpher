#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include "Entity.hpp"

class RenderWindow {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        RenderWindow(const char* p_title, int p_v, int p_h); 
        SDL_Texture* loadTexture(const char* p_filePath);
        void clear();
        void render(Entity &p_entity);
        void renderRotated(Entity &p_entity, double rotation);
        void display();
        void cleanup();
};
