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
    SDL_Texture* gameOverText = window.loadTexture("res/imgs/gameover.png");

    GlobalValues globalValues(0);
    
    SDL_Rect gameOverTextSrcRect;
    gameOverTextSrcRect.x = 400;
    gameOverTextSrcRect.y = 250;
    gameOverTextSrcRect.w = 525;
    gameOverTextSrcRect.h = 540;

    SDL_Rect gameOverTextDestRect;
    gameOverTextDestRect.x = WindowConstants::WIDTH/2 - (gameOverTextSrcRect.w - gameOverTextSrcRect.x)/2;
    gameOverTextDestRect.y = 300;
    gameOverTextDestRect.w = 960 - gameOverTextSrcRect.x;
    gameOverTextDestRect.h = 540 - gameOverTextSrcRect.y;

    Entity gameOverTextEntity(gameOverText, gameOverTextDestRect, gameOverTextSrcRect, &globalValues);

    SDL_Rect playerDestinationRect;
    playerDestinationRect.x = WindowConstants::WIDTH/2 -191;
    playerDestinationRect.y = 0;
    playerDestinationRect.h = 50;
    playerDestinationRect.w = 50;

    SDL_Rect playerTextureRect;
    playerTextureRect.x = 0;
    playerTextureRect.y = 0;
    playerTextureRect.h = 17;
    playerTextureRect.w = 17;  
    
    GravityFollowingEntity player(morpherTexture, playerDestinationRect, playerTextureRect, &globalValues, 0); 

    SDL_Rect platformDestinationRect;
    platformDestinationRect.x = WindowConstants::WIDTH/2 - 200;
    platformDestinationRect.y = 500;
    platformDestinationRect.h = 5;
    platformDestinationRect.w = 200;

    SDL_Rect platformDestinationRect2;
    platformDestinationRect2.x = 1000;
    platformDestinationRect2.y = 400;
    platformDestinationRect2.h = 5;
    platformDestinationRect2.w = 200;

    SDL_Rect platformTextureRect;
    platformTextureRect.x  = 0;
    platformTextureRect.y = 0;
    platformTextureRect.h = 3;
    platformTextureRect.w = 49;
    
    Platform platform1(&platformDestinationRect, &platformTextureRect, &player, platformTexture, &globalValues);
    Platform platform2(&platformDestinationRect2, &platformTextureRect, &player, platformTexture, &globalValues);
        
    Platform platforms[2] = {platform1, platform2};

    bool isRunning = true;
    
    SDL_Event event;
    
    float lastRenderTime = SDL_GetTicks();
    
    int cnt = 0;
    
    bool gameOver = false;
    int gameOverTime = 0;

    player.setY(platform1.getY() - player.getCurrentFrame()->h);
    player.setOnFloor(true);
    
    while (isRunning) {

        const Uint8* keyboardStates = SDL_GetKeyboardState(NULL);  
        if (keyboardStates[SDL_SCANCODE_W])
            if (player.isOnFloor()) {
                player.setOnFloor(false);
                player.addYVelocity(-25);
            }
        if (keyboardStates[SDL_SCANCODE_A])
            player.addXVelocity(-10);
        if (keyboardStates[SDL_SCANCODE_D])
            player.addXVelocity(10); 
        while (SDL_PollEvent(&event))
            switch(event.type) {
                case SDL_QUIT:
                      isRunning = false;
                      break;
                default:
                      break;
            }


         if (gameOver)
            player.moveTowardsCenter();
         else player.updateLocation();
    
        for (Platform &platform : platforms)
            platform.updateLocation();
 

        for (Platform &platform : platforms) {
            if (
                (player.getX() + player.getCurrentFrame()->w >= platform.getX() && player.getX() <= platform.getX() + platform.getCurrentFrame()->w)
                && (((player.getY() + player.getCurrentFrame()->h) < platform.getY() 
                && (player.getPredictedPositionY() + player.getCurrentFrame()->h) >= platform.getY()) || (player.getY() + player.getCurrentFrame()->h) == platform.getY())) {

                    player.setY(platform.getY() - player.getCurrentFrame()->h);
                    player.setOnFloor(true);
                    goto skip;         
            }

            player.setOnFloor(false);
        }

        skip: 

 
        // game over
        if (player.getY() + player.getCurrentFrame()->h == WindowConstants::HEIGHT && !gameOver) {
           gameOver = true;
           gameOverTime = SDL_GetTicks();
        }


        float curTime = SDL_GetTicks();
        float delayTime = std::max(0.0f, WindowConstants::FRAME_TIME_MILLISECONDS - (curTime - lastRenderTime)); 
        
        if (delayTime)
            SDL_Delay(delayTime);

        lastRenderTime = curTime; 
        
        window.clear();
        for (auto &platform : platforms)
            window.render(platform); 
        
        if (gameOver) {
            window.renderRotated(player, (SDL_GetTicks() - gameOverTime)/3.0);
            globalValues.setWindowY(gameOverTime - SDL_GetTicks());
            window.render(gameOverTextEntity);
        } else window.render(player);
        window.display(); 
          }
    

    
    window.cleanup();
    SDL_Quit();

    return 0;
}

