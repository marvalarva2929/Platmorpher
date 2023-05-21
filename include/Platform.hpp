#pragma once
#include <SDL2/SDL.h>
#include <iostream>

#include "Entity.hpp"
#include "GlobalValues.hpp"
#include "GravityFollowingEntity.hpp"

class Platform : public Entity {
    public:
        Platform(
                SDL_Rect* currentFrameRect, 
                SDL_Rect* textureRect, 
                GravityFollowingEntity* p_player, 
                SDL_Texture* p_texture,
                GlobalValues* p_globalValues);
        void updateLocation();
    private:
        GravityFollowingEntity* player;
        int absoluteX, absoluteY;
};
