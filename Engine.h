//
// Created by user on 6/15/2025.
//

#ifndef ENGINE_H
#define ENGINE_H
#include "Window.h"

class Engine {
    static int screenWidth, screenHeight;
    static bool isRunning, editorMode;
    Window& window;

public:
    Engine();
    Engine(int& width, int& height);
    ~Engine();

    static int getScreenWidth() { return screenWidth; }
    static int getScreenHeight() { return screenHeight; }
    bool running() { return isRunning; }
    static void setMode(const bool& mode) { editorMode = mode; }
};

#endif //ENGINE_H
