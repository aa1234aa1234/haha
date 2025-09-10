//
// Created by sw_306 on 2025-09-10.
//

#ifndef PROJECT_CAMERACOMPONENT_H
#define PROJECT_CAMERACOMPONENT_H
#include "NodeComponent.h"


class CameraComponent : public NodeComponent{
    const float YAW = -90.0f, PITCH = 0.0f;
    const float FOV = 95.0f;
    const float SENSITIVITY = 0.1f;
    const float SPEED = 10.0f;
public:
    CameraComponent() {}
    ~CameraComponent() {}

    virtual void update(float deltaTime);
};


#endif //PROJECT_CAMERACOMPONENT_H