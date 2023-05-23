#include <SDL2/SDL.h>

#include "GlobalValues.hpp"

GlobalValues::GlobalValues(int initialWindowX) : currentWindowX(initialWindowX) {};


void GlobalValues::addWindowX(int toAdd) { currentWindowX += toAdd; }
void GlobalValues::setWindowX(int toSet) { currentWindowX = toSet; }

void GlobalValues::addWindowY(int toAdd) { currentWindowY += toAdd; }
void GlobalValues::setWindowY(int toSet) { currentWindowY = toSet; }

int GlobalValues::getWindowX() { return currentWindowX; }
int GlobalValues::getWindowY() { return currentWindowY; }
