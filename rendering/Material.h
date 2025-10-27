//
// Created by sw_306 on 2025-10-27.
//

#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H
#include "header.h"

class Texture;
class Shader;

class Material {
    std::string name;
    Texture* diffuseMap;
    Texture* specularMap;
    Texture* normalMap;
};


#endif //PROJECT_MATERIAL_H