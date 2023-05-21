#pragma once
#include <SDL2/SDL.h>

class GlobalValues {
    public:
        GlobalValues(int initalWindowX);
        void addWindowX(int toAdd);
        void setWindowX(int toSet);
        int getWindowX();
    private:
        int currentWindowX;
};
