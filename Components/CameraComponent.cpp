//
// Created by sw_306 on 2025-09-10.
//

#include "CameraComponent.h"

#include "Engine.h"
#include "Input.h"

void CameraComponent::update(float deltaTime) {
    //might make a cameracompnentcontroller class
    int inputType = Input::EventType::MOUSE_DRAG;
    if (!Engine::getMode()) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        inputType = Input::EventType::MOUSE_MOVE;
    }

    if (Input::getInstance()->getEventType() == inputType) {
        float sensitivity = 0.2f;
        glm::vec2 mouseOffset = Input::getInstance()->getMouseDelta();
        mouseOffset.x *= sensitivity;
        mouseOffset.y *= sensitivity;
        yaw += mouseOffset.x;
        pitch += mouseOffset.y;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        setRotation(glm::vec2(pitch,yaw));
    }
    cameraspeed = 2.0f * deltaTime;
    if (Input::getInstance()->isKeyDown('w')) {
        position += cameraspeed * front;
    }
    if (Input::getInstance()->isKeyDown('s')) {
        position -= cameraspeed * front;
    }
    if (Input::getInstance()->isKeyDown('a')) position -= glm::normalize(glm::cross(front, up)) * cameraspeed;
    if (Input::getInstance()->isKeyDown('d')) position += glm::normalize(glm::cross(front, up)) * cameraspeed;
    if (Input::getInstance()->isKeyDown(' ')) position += cameraspeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::getInstance()->isKeyDown(340)) position += cameraspeed * glm::vec3(0.0f, -1.0f, 0.0f);
}

void CameraComponent::rescale(const int& width, const int& height) {
    screenWidth = width;
    screenHeight = height;
    getProjectionMatrix();
}

void CameraComponent::updateCameraVectors() {
    glm::vec3 front2;
    front2.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front2.y = sin(glm::radians(pitch));
    front2.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front2);
}

void CameraComponent::setRotation(const glm::vec2& rot) {
    pitch = rot.x;
    yaw = rot.y;
    updateCameraVectors();
}

glm::mat4 CameraComponent::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 CameraComponent::getProjectionMatrix() {
    projection = glm::perspective(glm::radians(zoom),static_cast<float>(screenWidth)/static_cast<float>(screenHeight), zNear, zFar);
    return projection;
}
