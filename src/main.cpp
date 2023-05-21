#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#define nl '\n'

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "GravityFollowingEntity.hpp"
#include "Constants.cpp"
#include "GlobalValues.hpp"
#include "Platform.hpp"

int main(int argc, char* args[]) {
     
    if (SDL_Init(SDL_INIT_VIDEO)) 
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << nl; 
    
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << nl;
    
    RenderWindow window("Platmorpher", WindowConstants::WIDTH, WindowConstants::HEIGHT);    
    SDL_Texture* morpherTexture = window.loadTexture("res/imgs/normal.gif");
    SDL_Texture* platformTexture = window.loadTexture("res/imgs/platform.gif");
    
    GlobalValues globalValues(0);
    SDL_Rect playerDestinationRect;
    playerDestinationRect.x = WindowConstants::WIDTH/2;
    playerDestinationRect.y = 383;
    playerDestinationRect.h = 50;
    playerDestinationRect.w = 50;

    SDL_Rect playerTextureRect;
    playerTextureRect.x = 0;
    playerTextureRect.y = 0;
    playerTextureRect.h = 17;
    playerTextureRect.w = 17;  
    
    GravityFollowingEntity player(morpherTexture, playerDestinationRect, playerTextureRect, &globalValues, 0); 

    SDL_Rect platformDestinationRect;
    platformDestinationRect.x = WindowConstants::WIDTH/2;
    platformDestinationRect.y = 500;
    platformDestinationRect.h = 5;
    platformDestinationRect.w = 150;

    SDL_Rect platformTextureRect;
    platformTextureRect.x  = 0;
    platformTextureRect.y = 0;
    platformTextureRect.h = 3;
    platformTextureRect.w = 49;
    
    Platform platform(&platformDestinationRect, &platformTextureRect, &player, platformTexture, &globalValues);
    bool isRunning = true;
    
    SDL_Event event;
    
    float lastRenderTime = SDL_GetTicks();
    
    int cnt = 0;

    while (isRunning) {

        const Uint8* keyboardStates = SDL_GetKeyboardState(NULL);  
       
        if (keyboardStates[SDL_SCANCODE_W])
            if (player.isOnFloor()) {
                player.setOnFloor(false);
                player.addYVelocity(-30);
            }
        if (keyboardStates[SDL_SCANCODE_A])
            globalValues.addWindowX(5);
        if (keyboardStates[SDL_SCANCODE_D])
            globalValues.addWindowX(-5);
        
        while (SDL_PollEvent(&event))
            switch(event.type) {
                case SDL_QUIT:
                      isRunning = false;
                      break;
                default:
                      break;
            }
    
        //if (!(cnt++ % 30))
        player.updateLocation();
    
        platform.updateLocation();
    
        if (player.getY() + player.getCurrentFrame()->h == 720)
            player.setOnFloor(true);
        else if (
                (player.getX() >= platform.getX() && player.getX() + player.getCurrentFrame()->w <= platform.getX() + platform.getCurrentFrame()->w)
                && (((player.getY() + player.getCurrentFrame()->h) < platform.getY() && (player.getPredictedPosition() + player.getCurrentFrame()->h) >= platform.getY()) || (player.getY() + player.getCurrentFrame()->h) == platform.getY())) {
                    player.setOnFloor(true);
                    player.setY(platform.getY() - player.getCurrentFrame()->h);
        } else {
            player.setOnFloor(false);
        }
        float curTime = SDL_GetTicks();
        float delayTime = std::max(0.0f, WindowConstants::FRAME_TIME_MILLISECONDS - (curTime - lastRenderTime)); 
        
        if (delayTime)
            SDL_Delay(delayTime);

        lastRenderTime = curTime; 
        
        window.clear(); 
        window.render(platform); 
        window.render(player);
        window.display(); 
    }
    
    
    window.cleanup();
    SDL_Quit();

    return 0;
}

