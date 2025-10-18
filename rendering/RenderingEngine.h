//
// Created by sw_306 on 2025-10-15.
//

#ifndef PROJECT_RENDERINGENGINE_H
#define PROJECT_RENDERINGENGINE_H
#include "header.h"

class Engine;
class SkyBox;
class CameraComponent;
class SceneNode;

class RenderingEngine {
    std::vector<std::string> cubeMapFaces = {
        "resources/textures/cubemap/right.jpg",
        "resources/textures/cubemap/left.jpg",
        "resources/textures/cubemap/top.jpg",
        "resources/textures/cubemap/bottom.jpg",
        "resources/textures/cubemap/back.jpg",
        "resources/textures/cubemap/front.jpg"
    };
    Engine* engine=nullptr;
    SkyBox* skybox=nullptr;
    CameraComponent* sceneCamera=nullptr;
    CameraComponent* editorCamera=nullptr;
public:
    RenderingEngine(Engine* engine);
    ~RenderingEngine();

    void render(SceneNode* scenenode);
};


#endif //PROJECT_RENDERINGENGINE_H