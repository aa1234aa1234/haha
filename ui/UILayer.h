//
// Created by D412 on 2025-06-16.
//

#ifndef UILAYER_H
#define UILAYER_H
#include "Engine.h"
#include "UIContext.h"
#include "Window.h"

//entire class needs to be touched up on

class Engine;

class UILayer {

    Engine* engine = nullptr;
public:
    UILayer(Engine* engine);
    ~UILayer();
    void init(Window& window);

    void render();

    void handlevent();
};



#endif //UILAYER_H
