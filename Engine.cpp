//
// Created by user on 6/15/2025.
//

#include "Engine.h"

int Engine::screenHeight, Engine::screenWidth;
bool Engine::isRunning = false;
bool Engine::editorMode = false;

Engine::Engine(int& width, int& height) {
    screenWidth = width;
    screenHeight = height;

}