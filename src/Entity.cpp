#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <iostream>

#include "Entity.hpp"
#include "Constants.cpp"

Entity::Entity(SDL_Texture* p_texture, SDL_Rect& p_dest, SDL_Rect& p_textureFrame, GlobalValues* p_globalValues) :
    texture(p_texture), 
    currentFrame(p_dest), 
    textureFrame(p_textureFrame), 
    globalValues(p_globalValues) {
    }

void Entity::addX(int toAdd) { 
    toAdd = std::min(WindowConstants::WIDTH - currentFrame.x - currentFrame.w, toAdd);
    toAdd = std::max(-currentFrame.x, toAdd);
    currentFrame.x += toAdd;
}
void Entity::addY(int toAdd) {
    toAdd = std::min(WindowConstants::HEIGHT - currentFrame.y - currentFrame.h, toAdd);
    toAdd = std::max(-currentFrame.y, toAdd);  
    currentFrame.y += toAdd; 
}

void Entity::setX(int toSet) { currentFrame.x = toSet; }
void Entity::setY(int toSet) { currentFrame.y = toSet; }

int Entity::getX() { return currentFrame.x; }
int Entity::getY() { return currentFrame.y; }

SDL_Texture* Entity::getTexture() { return texture; }
SDL_Rect* Entity::getCurrentFrame() { return &currentFrame; }
SDL_Rect* Entity::getTextureFrame() { return &textureFrame; }
