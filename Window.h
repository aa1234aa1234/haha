//
// Created by user on 6/15/2025.
//

#ifndef WINDOW_H
#define WINDOW_H
#include "header.h"


class Window {
    GLFWwindow* window;
public:
    Window();
    Window(int& width, int& height, std::string title);
    ~Window();

    void swapBuffers();
    void init(int& width, int& height, std::string title);
};



#endif //WINDOW_H
