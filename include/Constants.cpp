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
};

class PhysicsConstants {
    public:
        const static int accelerationConstant = 3;
        const static int maxVelocity = 10;
};
    
