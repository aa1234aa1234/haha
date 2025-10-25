//
// Created by user on 6/15/2025.
//

#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Window.h"
#include "Application.h"
#include "UILayer.h"
#include "EditorLayer.h"
#include "FrameBuffer.h"
#include "EventDispatcher.h"
#include "FrameLimiter.h"
#define FRAME_LIMIT 144

class CameraComponent;
class UILayer;
class EventDispatcher;
class RenderingEngine;

class Engine {


    static int screenWidth, screenHeight;
    static bool isRunning, editorMode;
    float deltatime=0.0;
    Window window;
    Application* application=nullptr;
    UILayer* uiLayer=nullptr;
    EditorLayer* editorLayer=nullptr;
    FrameBuffer* sceneBuffer=nullptr;
    EventDispatcher* eventDispatcher=nullptr;
    FrameLimiter frameLimiter = FrameLimiter(FRAME_LIMIT);
    CameraComponent* sceneCamera=nullptr;
    CameraComponent* editorCamera=nullptr;
    RenderingEngine* renderingEngine=nullptr;

public:
    Engine();
    Engine(Application* app, const int& width, const int& height, const std::string& title);
    ~Engine();

    static int getScreenWidth() { return screenWidth; }
    static int getScreenHeight() { return screenHeight; }
    bool running() { return isRunning; }
    static void setMode(const bool& mode) { editorMode = mode; }
    static void setRunning(const bool& running) { isRunning = running; }
    static bool getMode() { return editorMode; }
    float getDeltaTime() { return deltatime; }
    CameraComponent* getSceneCamera() { return sceneCamera; }
    CameraComponent* getEditorCamera() { return editorCamera; }
    FrameBuffer* getSceneBuffer() { return sceneBuffer; }
    EventDispatcher* getEventDispatcher() { return eventDispatcher; }
    Application* getApplication() { return application; }
    Window& getWindow() { return window; }

    void run();
    void render(float deltatime);
    void handleInput(float deltatime, InputEvent event);
};

#endif //ENGINE_H
