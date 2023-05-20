#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h> 
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <map>

class WindowConstants {
    public:
        const static int WIDTH = 1280;
        const static int HEIGHT = 720;
        const static int MAX_FPS = 60;
        constexpr static float FRAME_TIME_MILLISECONDS = (1000.0f * (1.0f / MAX_FPS));
};

class PhysicsConstants {
    public:
        const static int accelerationConstant = 1;
        const static int maxVelocity = 10;
};
    
