#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "Entity.hpp"
#include "Constants.cpp"

class GravityFollowingEntity : public Entity {
    public:
        GravityFollowingEntity(SDL_Texture* p_texture, SDL_Rect& p_textureRect, SDL_Rect& p_destinationRect, int p_initalVel);
        void updateLocation();
        void addYVelocity(int toAdd);
    private:
        int currentYVel;
        int accelerationConstant = PhysicsConstants::accelerationConstant;
};
