//
// Created by user on 2026-03-11.
//

#include "Light.h"

#include "Shader.h"

BaseLight::BaseLight() {
    delete shader;
}

BaseLight::~BaseLight() {}