//
// Created by user on 6/15/2025.
//

#include "Engine.h"

int Engine::screenHeight, Engine::screenWidth;
bool Engine::isRunning = false;
bool Engine::editorMode = false;

Engine::Engine(int& width, int& height) : window() {
    screenWidth = width;
    screenHeight = height;
    window.init(width,height,"fewafwea");
}

Engine::~Engine()
{
    delete app;
}

void Engine::run()
{
    double deltatime = 0.0, lastframe = 0.0;


    while (isRunning)
    {
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastframe;
        lastframe = currentFrame;

        //normal engine code holy shit im making comments omg
        if (!editorMode) {}
        render(deltatime);
        //ill leave this here need to making editor layer
        window.swapBuffers();
    }

}

void Engine::render(float deltatime)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}
