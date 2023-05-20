#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#define nl '\n'

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "GravityFollowingEntity.hpp"
#include "Constants.cpp"

void manageKeyPress(const Uint8* keybaordStates, GravityFollowingEntity &player) {
    if (keybaordStates[SDL_SCANCODE_W])
        if (player.getY() + player.getCurrentFrame().h == 720)
            player.addYVelocity(-1);
    if (keybaordStates[SDL_SCANCODE_A])
        player.addX(-1);
    if (keybaordStates[SDL_SCANCODE_D])
        player.addX(1);
}

int main(int argc, char* args[]) {
     
    if (SDL_Init(SDL_INIT_VIDEO)) 
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << nl; 
    
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << nl;
    
    RenderWindow window("Platmorpher", WindowConstants::WIDTH, WindowConstants::HEIGHT);
    
    SDL_Texture* morpherTexture = window.loadTexture("res/imgs/normal.gif");

    SDL_Rect playerDestinationRect;
    playerDestinationRect.x = 10;
    playerDestinationRect.y = 10;
    playerDestinationRect.h = 50;
    playerDestinationRect.w = 50;

    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;
    textureRect.h = 17;
    textureRect.w = 17;  
    
    int cnt = 0;
    
    GravityFollowingEntity player(morpherTexture, playerDestinationRect, textureRect, 0); 
        
    bool isRunning = true;
    
    SDL_Event event;
    
    while (isRunning) {
        const Uint8* keyboardStates = SDL_GetKeyboardState(NULL);  
        manageKeyPress(keyboardStates, player);

        while (SDL_PollEvent(&event))
            switch(event.type) {
                case SDL_QUIT:
                      isRunning = false;
                      break;
                case SDL_KEYDOWN:    
                    break;
                default:
                      break;
            }
        
        if (!(cnt++ % 40)) {
            player.updateLocation();
        }

        window.clear();
        window.render(player);
        window.display();
    }
    
    
    window.cleanup();
    SDL_Quit();

    return 0;
}

