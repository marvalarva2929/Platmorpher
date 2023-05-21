#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#define nl '\n'

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) :window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    
    if (window == NULL) 
       std::cout << "Window failed to INIT. Error: " << SDL_GetError() << nl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);
    
    if (texture == NULL)
        std::cout << "Texture " << p_filePath << " failed to load. Error: " << SDL_GetError() << nl;

    return texture;
}

void RenderWindow::render(Entity &p_entity) {
    SDL_Rect src = *p_entity.getTextureFrame();
    SDL_Rect dest = *p_entity.getCurrentFrame();

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanup() {
    SDL_DestroyWindow(window);
}


