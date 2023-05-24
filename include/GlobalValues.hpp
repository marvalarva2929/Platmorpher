#pragma once
#include <SDL2/SDL.h>

class GlobalValues {
    public:
        GlobalValues(int initalWindowX);
        void addWindowX(int toAdd);
        void setWindowX(int toSet);
        void addWindowY(int toAdd);
        void setWindowY(int toSet);
        int getWindowY();
        int getWindowX();
    private:
        int currentWindowY = 0;
        int currentWindowX = 0;
};
