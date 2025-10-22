//
// Created by D412 on 2025-06-16.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"
#include "SceneNode.h"

#include "EventDispatcher.h"
#include "InputEvent.h"

class RenderingEngine;

typedef void (*glfw_error_handler_function)(void* user_data, int error_code, const char* description);
thread_local static struct ErrorHandler {
    void* user_data;
    glfw_error_handler_function handler;
} error_handler = {NULL, NULL};

static void globalErrorHandler(int error_code, const char* description) {
    if (error_handler.handler != NULL) {
        error_handler.handler(error_handler.user_data, error_code, description);
    }
}

struct InputEvents {
    InputEvent mouseDown, mouseUp, mouseMove, mouseDrag, keyDown, keyUp, scroll;
};

class Application {


    SceneNode root;
    std::map<int,int> inputCnt;
    std::map<int, std::queue<InputEvent>> inputEvent;
    glm::vec2 lastMousePos;
    bool firstMouse = true;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void error_callback(void* user_data, int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->key_callback(window, key, scancode, action, mods);
    }
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->mouse_callback(window, button, action, mods);
    }
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
        Application *app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->cursorpos_callback(window, xpos, ypos); }
    }
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->scroll_callback(window, xoffset, yoffset); }
    }
public:
    Application();
    ~Application();

    std::map<int,std::queue<InputEvent>>& getInputEvents() { return inputEvent; }
    void pollInputEvent(InputEvents& event)
    {

        event = {inputEvent[0].back(),inputEvent[1].back(),inputEvent[2].back(),inputEvent[3].back(),inputEvent[4].back(),inputEvent[5].back(),inputEvent[6].back()};
    }
    SceneNode& getRoot() { return root; }
    void render(RenderingEngine* renderingengine);
    void update(float deltatime);
    void handleInput(float deltatime);
    void popEvent();

    void setCallBack(GLFWwindow* window);
};





#endif //APPLICATION_H
