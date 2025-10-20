//
// Created by sw_306 on 2025-09-10.
//

#ifndef PROJECT_CAMERACOMPONENT_H
#define PROJECT_CAMERACOMPONENT_H
#include "NodeComponent.h"
#include "glm/glm.hpp"
#include "Application.h"


const float YAW = -90.0f, PITCH = 0.0f;
const float FOV = 95.0f;
const float SENSITIVITY = 0.1f;
const float SPEED = 10.0f;

class Engine;

class CameraComponent : public NodeComponent{
    int screenWidth, screenHeight;
    float yaw = -90.0f, pitch = 0.0f;
    float fov = 95.0f;
    float cameraspeed = 0.0f;
    float zoom = 0.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 worldUp;
    glm::vec3 up;
    glm::vec3 direction;
    glm::mat4 projection = glm::mat4(1.0f);
    GLFWwindow* window;
public:
    CameraComponent(GLFWwindow* window) : window(window), position(glm::vec3(0.0f, 1.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}
    ~CameraComponent() {}

    void update(float deltaTime) override;
    void rescale(const int& width, const int& height);
    void updateCameraVectors();
    void setRotation(const glm::vec2& rot);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};


#endif //PROJECT_CAMERACOMPONENT_H