//
// Created by user on 6/15/2025.
//

#include "Window.h"

Window::Window() {}

Window::Window(int& width, int& height, std::string title) {
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, width, height);
}

Window::~Window() {
    if (window != nullptr) {
        glfwTerminate();
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
    glFinish();
}
