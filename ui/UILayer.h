//
// Created by D412 on 2025-06-16.
//

#ifndef UILAYER_H
#define UILAYER_H
#include "Engine.h"
#include "UIContext.h"
#include "Window.h"

class Engine;

class UILayer {


    UIContext* context;
    Engine* engine = nullptr;
public:
    UILayer(Engine* engine);
    ~UILayer();
    void init(Window& window);

    void render();

    void handlevent();
};



#endif //UILAYER_H
