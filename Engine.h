//
// Created by user on 6/15/2025.
//

#ifndef ENGINE_H
#define ENGINE_H
#include "Window.h"
#include "Application.h"
#include "UILayer.h"
#include "EditorLayer.h"
#include "FrameBuffer.h"

class UILayer;

class Engine {


    static int screenWidth, screenHeight;
    static bool isRunning, editorMode;
    Window window;
    Application* application=nullptr;
    UILayer* uiLayer=nullptr;
    EditorLayer* editorLayer=nullptr;
    FrameBuffer* sceneBuffer=nullptr;

public:
    Engine();
    Engine(Application* app, const int& width, const int& height, const std::string& title);
    ~Engine();

    static int getScreenWidth() { return screenWidth; }
    static int getScreenHeight() { return screenHeight; }
    bool running() { return isRunning; }
    static void setMode(const bool& mode) { editorMode = mode; }
    static void setRunning(const bool& running) { isRunning = running; }
    FrameBuffer* getSceneBuffer() { return sceneBuffer; }

    void run();
    void render(float deltatime);
    void handleInput(float deltatime);
};

#endif //ENGINE_H
