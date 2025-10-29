//
// Created by sw_306 on 2025-10-27.
//

#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H
#include "header.h"

class Texture;
class Shader;

class Material {
    Texture* diffuseMap;
    Texture* specularMap;

    glm::vec4 diffuseColor{1.0f};
    glm::vec4 ambientColor{1.0f};
    glm::vec4 specularColor{1.0f};

protected:
    std::string name;
    Texture* normalMap;
    void deleteTextures();

public:
    Material(const std::string& name) : name(name) {}
    virtual ~Material() {}
};


#endif //PROJECT_MATERIAL_H