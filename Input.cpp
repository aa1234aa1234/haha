//
// Created by sw_303 on 2025-06-21.
//

#include "Input.h"

#include <algorithm>

Input* Input::instance = 0;

Input::Input() : mousepos(0.0,0.0), mousedelta(0.0,0.0) {}

Input::~Input() {}

std::unordered_map<char,bool> Input::getKeyDown()
{
    return keydown;
}

glm::vec2 Input::getMousePos()
{
    return mousepos;
}

glm::vec2 Input::getMouseDelta()
{
    return mousedelta;
}

void Input::setMousePos(const float& x, const float& y)
{
    mousepos.x = x;
    mousepos.y = y;
}

void Input::setMouseDelta(const float& x, const float& y)
{
    mousedelta.x = x;
    mousedelta.y = y;
}

void Input::setKeyDown(const char& key, bool down)
{
    keydown[key] = down;
}

bool Input::isKeyDown(const char& key)
{
    return keydown.find(key) != keydown.end();
}

