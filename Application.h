//
// Created by D412 on 2025-06-16.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"
#include "SceneNode.h"

#include "EventHandler.h"

class Application {
    SceneNode root;
    std::queue<IEvent*> inputEvent;
    glm::vec2 lastMousePos;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, int button, int action, int mods);
public:
    Application();
    ~Application();
    std::queue<IEvent*>& getInputEvent() { return inputEvent; }
    IEvent* getLastInput() { IEvent* e = inputEvent.front(); inputEvent.pop(); return e; }

    void render();
    void update();
    void handleInput();
};



#endif //APPLICATION_H
