//
// Created by sw_303 on 2025-06-21.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>

class Transform
{
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
public:
    Transform() {}
    Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) : translation(translation), rotation(rotation), scale(scale) {};
    ~Transform() {}
    void setTranslation(const glm::vec3& translation) { this->translation = translation; }
    void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
    void setScale(const glm::vec3& scale) { this->scale = scale; }
    glm::vec3 getTranslation() const { return this->translation; }
    glm::vec3 getRotation() const { return this->rotation; }
    glm::vec3 getScale() const { return this->scale; }

};

#endif //TRANSFORM_H
