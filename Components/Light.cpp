//
// Created by user on 2026-03-11.
//

#include "Light.h"

BaseLight::BaseLight() {
    delete shader;
}

BaseLight::~BaseLight() {}