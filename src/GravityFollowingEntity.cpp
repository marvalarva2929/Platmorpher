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
        GlobalValues* p_globalValues,
        int p_initalVel) : Entity(p_texture, p_textureRect, p_destinationRect, p_globalValues), currentYVel(p_initalVel) {}

void GravityFollowingEntity::addYVelocity(int toAdd) { 
    currentYVel += toAdd; 
    //currentYVel = std::min(currentYVel, 10);
    //currentYVel = std::max(currentYVel, -10);
}

void GravityFollowingEntity::updateLocation() {
    if (!onFloor) {
        currentYVel += accelerationConstant;
    } else {
        currentYVel = 0;
        predictedPosition = getY();
    }

    addY(currentYVel);

    if (!onFloor)
        predictedPosition = getY() + currentYVel + accelerationConstant; 
}

void GravityFollowingEntity::setOnFloor(bool toSet) { onFloor = toSet; }

int GravityFollowingEntity::getPredictedPosition() { return predictedPosition; }

bool GravityFollowingEntity::isOnFloor() { return onFloor; } 
