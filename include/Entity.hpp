#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "GlobalValues.hpp"

class Entity {
    public:
        Entity(SDL_Texture* p_texture, SDL_Rect& p_textureRect, SDL_Rect& p_destinationRect, GlobalValues* p_globalValues);
        int getX();
        int getY();
        void addX(int toAdd);
        void addY(int toAdd);
        void setX(int toSet);
        void setY(int toSet);
        SDL_Texture* getTexture();
        SDL_Rect* getCurrentFrame();
        SDL_Rect* getTextureFrame();

    protected:
        SDL_Texture* texture; 
        SDL_Rect currentFrame;
        SDL_Rect textureFrame;
        GlobalValues* globalValues;
};

