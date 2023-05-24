#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>
#define nl '\n'

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "GravityFollowingEntity.hpp"
#include "Constants.cpp"
#include "GlobalValues.hpp"
#include "Platform.hpp"

SDL_Rect getRect(int x, int y, int w, int h) {
    SDL_Rect ret;
    ret.x = x;
    ret.y = y;
    ret.w = w;
    ret.h = h;

    return ret;
}

int main(int argc, char* args[]) {
     
    if (SDL_Init(SDL_INIT_VIDEO)) 
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << nl; 
    
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << nl;
    
    RenderWindow window("Platmorpher", WindowConstants::WIDTH, WindowConstants::HEIGHT);    
   
    // Textures 
    SDL_Texture* morpherTexture = window.loadTexture("res/imgs/normal.gif");
    SDL_Texture* platformTexture = window.loadTexture("res/imgs/platform.gif");
    SDL_Texture* gameOverText = window.loadTexture("res/imgs/gameover.png");
   
    // SRC Rects 
    SDL_Rect platformTextureRect = getRect(0, 0, 3, 49);   
    SDL_Rect gameOverTextSrcRect = getRect(400, 250, 525, 540); 
    SDL_Rect playerTextureRect = getRect(0, 0, 17, 17);
    
    // DEST Rects
    SDL_Rect platformDestinationRect1 = getRect(WindowConstants::WIDTH/2, 600, 100, 5);
    SDL_Rect platformDestinationRect2 = getRect(WindowConstants::WIDTH/2 + 200, 400, 100, 5);
    SDL_Rect platformDestinationRect3 = getRect(WindowConstants::WIDTH/2 + 400, 700, 100, 5);
    SDL_Rect gameOverTextDestRect = getRect(WindowConstants::WIDTH/2 - (gameOverTextSrcRect.w - gameOverTextSrcRect.x)/2, 300, 960 - gameOverTextSrcRect.x, 540 - gameOverTextSrcRect.y);
    SDL_Rect playerDestinationRect = getRect(WindowConstants::WIDTH/2, 0, 50, 50);
    
    // Entities
    GlobalValues globalValues(0);
    Entity gameOverTextEntity(gameOverText, gameOverTextDestRect, gameOverTextSrcRect, &globalValues);
    GravityFollowingEntity player(morpherTexture, playerDestinationRect, playerTextureRect, &globalValues, 0); 
    Platform platform1(&platformDestinationRect1, &platformTextureRect, &player, platformTexture, &globalValues);
    Platform platform2(&platformDestinationRect2, &platformTextureRect, &player, platformTexture, &globalValues);
    Platform platform3(&platformDestinationRect3, &platformTextureRect, &player, platformTexture, &globalValues);

    std::vector<Platform> platforms = {platform1, platform2, platform3};

    bool isRunning = true; 
    SDL_Event event;
    
    float lastRenderTime = SDL_GetTicks();
    
    bool gameOver = false;
    int gameOverTime = 0;

    player.setY(platform1.getY() - player.getCurrentFrame()->h - 10);
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
            }

         if (gameOver)
            player.moveTowardsCenter();
         else player.updateLocation();
       
        for (Platform &platform : platforms) {
            platform.updateLocation();
            

            bool inBetweenX = 
                player.getX() + player.getCurrentFrame()->w >= platform.getX()
                && player.getX() <= platform.getX() + platform.getCurrentFrame()->w;

            bool inBetweenY = 
                (player.getY() + player.getCurrentFrame()->h < platform.getY()
                && player.getPredictedPositionY() + player.getCurrentFrame()->h >= platform.getY())
                || player.getY() + player.getCurrentFrame()->h == platform.getY();
            
            if (inBetweenX && inBetweenY) {
                player.setY(platform.getY() - player.getCurrentFrame()->h);
                player.setOnFloor(true);
                goto skip;
            }
            
          player.setOnFloor(false);
        }
        
skip:
        // game over
        if (player.getY() + player.getCurrentFrame()->h >= WindowConstants::HEIGHT && !gameOver) {
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

