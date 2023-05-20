#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"
#include "GravityFollowingEntity.hpp"
#include "Constants.cpp"

#define nl '\n'

GravityFollowingEntity::GravityFollowingEntity(
        SDL_Texture* p_texture, 
        SDL_Rect& p_textureRect,
        SDL_Rect& p_destinationRect, 
        int p_initalVel) : Entity(p_texture, p_textureRect, p_destinationRect), currentYVel(p_initalVel) {}

void GravityFollowingEntity::addYVelocity(int toAdd) { 
    currentYVel += toAdd; 
    //currentYVel = std::min(currentYVel, 10);
    //currentYVel = std::max(currentYVel, -10);
}
// updates the yLocation of the entity by simulating gravity
void GravityFollowingEntity::updateLocation() {
    addY(currentYVel);
    if (currentFrame.y + currentFrame.h < WindowConstants::HEIGHT) currentYVel += accelerationConstant; 
    else currentYVel = 0;
}
