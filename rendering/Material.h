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
    Material() = default;
    virtual ~Material() {}

    void setDiffuseMap(Texture* diffuseMap);
    void setSpecularMap(Texture* specularMap);
    void setNormalMap(Texture* normalMap);

    void setAmbientColor(glm::vec4 ambientColor);
    void setSpecularColor(glm::vec4 specularColor);
    void setDiffuseColor(glm::vec4 diffuseColor);
};


#endif //PROJECT_MATERIAL_H