#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "Entity.hpp"
#include "Constants.cpp"
#include "GlobalValues.hpp"

class GravityFollowingEntity : public Entity {
    public:
        GravityFollowingEntity(SDL_Texture* p_texture, SDL_Rect& p_textureRect, SDL_Rect& p_destinationRect, GlobalValues* p_globalValues,  int p_initalVel);
        void updateLocation();
        void addYVelocity(int toAdd);
        void addXVelocity(int toAdd);
        void setOnFloor(bool toSet);
        void moveTowardsCenter();
        int getPredictedPositionY();
        int getPredictedPositionX();
        bool isOnFloor();
    private:
        bool onFloor = false;
        int currentYVel;
        int currentXVel = 0;
        int accelerationConstant = PhysicsConstants::accelerationConstant;
        int predictedY;
        int predictedX;
};
