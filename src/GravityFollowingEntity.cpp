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

void GravityFollowingEntity::addXVelocity(int toAdd) {
    currentXVel += toAdd;
    currentXVel = std::min(currentXVel, 10);
    currentXVel = std::max(currentXVel, -10);
}

void GravityFollowingEntity::updateLocation() {
    if (!onFloor) {
        currentYVel += accelerationConstant;
    } else {
        currentYVel = 0;
        predictedY = getY();
    }
    
    globalValues->addWindowX(-currentXVel);
    addY(currentYVel);
    
    currentXVel -= (int)ceil((double)currentXVel)/1.1f;

    predictedX = getX() + currentXVel;

    if (!onFloor)
        predictedY = getY() + currentYVel + accelerationConstant; 
    
}

void GravityFollowingEntity::moveTowardsCenter() {
   int centerH = WindowConstants::HEIGHT/2;

    addY((centerH - getY())/20);
}

void GravityFollowingEntity::setOnFloor(bool toSet) { onFloor = toSet; }

int GravityFollowingEntity::getPredictedPositionY() { return predictedY; }

int GravityFollowingEntity::getPredictedPositionX() { return predictedX; }

int GravityFollowingEntity::getYVelocity() { return currentYVel; }

int GravityFollowingEntity::getXVelocity() { return currentXVel; } 

bool GravityFollowingEntity::isOnFloor() { return onFloor; } 
