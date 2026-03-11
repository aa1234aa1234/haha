//
// Created by user on 2026-03-11.
//

#ifndef LIGHT_H
#define LIGHT_H
#include "glm/glm.hpp"
#include "NodeComponent.h"

class Shader;

class BaseLight : public NodeComponent {
protected:
    Shader* shader;
public:
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    BaseLight();
    BaseLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) : ambientColor(ambient), diffuseColor(diffuse), specularColor(specular), shader(nullptr) {}
    ~BaseLight();

    void setShader(Shader* shader) { this->shader = shader; }
    Shader* getShader() { return shader; }
};



#endif //LIGHT_H
