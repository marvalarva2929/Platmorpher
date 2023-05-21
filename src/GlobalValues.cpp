#include <SDL2/SDL.h>

#include "GlobalValues.hpp"

GlobalValues::GlobalValues(int initialWindowX) : currentWindowX(initialWindowX) {};

int GlobalValues::getWindowX() { return currentWindowX; }

void GlobalValues::setWindowX(int toSet) { currentWindowX = toSet; }

void GlobalValues::addWindowX(int toAdd) { currentWindowX += toAdd; }


