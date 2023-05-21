#include <SDL2/SDL.h>

#include "GlobalValues.hpp"
#include "Platform.hpp"
#include "Entity.hpp"

#define nl '\n'

Platform::Platform(
        SDL_Rect* currentFrameRect, 
        SDL_Rect* textureRect,
        GravityFollowingEntity* p_player, 
        SDL_Texture* p_texture,
        GlobalValues* p_globalValues) : 
    Entity(p_texture, *currentFrameRect, *textureRect, p_globalValues),    
    player(p_player),
    absoluteX(currentFrameRect->x),
    absoluteY(currentFrameRect->y) {};

void Platform::updateLocation() {
    setX(globalValues->getWindowX() + absoluteX);
}
