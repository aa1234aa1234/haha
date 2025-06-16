//
// Created by D412 on 2025-06-16.
//

#include "UILayer.h"

UILayer::UILayer(Engine* engine) : engine(engine)
{

}

UILayer::~UILayer()
{
    delete context;
}

void UILayer::init(Window& window)
{
    context = new UIContext();
    context->init(window.getWidth(), window.getHeight());
}

void UILayer::render()
{
    context->DrawComponents();
}

void UILayer::handlevent()
{

}

