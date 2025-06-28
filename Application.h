//
// Created by D412 on 2025-06-16.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"
#include "SceneNode.h"

class Application {
    SceneNode root;
public:
    Application();
    ~Application();

    void run();
    void render();
    void handleInput();
};



#endif //APPLICATION_H
