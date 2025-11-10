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

    float shininess=32.0f;

protected:
    std::string name;
    Texture* normalMap;
    void deleteTextures();

public:
    Material(const std::string& name) : name(name) {}
    Material() = default;
    virtual ~Material() {}

    void setDiffuseMap(Texture* diffuseMap) { this->diffuseMap = diffuseMap; }
    void setSpecularMap(Texture* specularMap) { this->specularMap = specularMap; }
    void setNormalMap(Texture* normalMap) { this->normalMap = normalMap; }

    void setAmbientColor(glm::vec4 ambientColor) { this->ambientColor = ambientColor; }
    void setSpecularColor(glm::vec4 specularColor) { this->specularColor = specularColor; }
    void setDiffuseColor(glm::vec4 diffuseColor) { this->diffuseColor = diffuseColor; }

    virtual void UpdateUniforms(Shader& shader);
};


#endif //PROJECT_MATERIAL_H