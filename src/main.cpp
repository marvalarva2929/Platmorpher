#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define nl '\n'
using namespace std;

int main(int argc, char* args[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO)) 
        cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << nl; 
    
    if (!IMG_Init(IMG_INIT_PNG))
        cout << "IMG_init has failed. Error: " << SDL_GetError() << nl;
    
    RenderWindow window("Game v1.0", 1280, 720);
    
    SDL_Texture* morpherTexture = window.loadTexture("res/imgs/normal.gif");

    bool isRunning = true;
    
    SDL_Event event;

    while (isRunning) { 
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                isRunning = false;
        
       window.clear();
       window.render(morpherTexture);
       window.display();
    }
    
    
    window.cleanup();
    SDL_Quit();

    return 0;
}
