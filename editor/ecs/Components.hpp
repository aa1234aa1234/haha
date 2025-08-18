//
// Created by D412 on 2025-08-13.
//
#pragma once
#ifndef COMPONENTS_H
#include <vector>

#include "Entity.h"

struct TransformComponent
{
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
};

struct ContentComponent
{
    std::vector<Entity*> entities;
};

struct ScrollableComponent
{
    bool horizontal, vertical;
    int offset;
    int maxScroll;
};


#define COMPONENTS_H

#endif //COMPONENTS_H
