//
// Created by sw_306 on 2025-10-15.
//

#include "RenderingEngine.h"
#include "Engine.h"
#include "SkyBox.h"

RenderingEngine::RenderingEngine(Engine* engine) : engine(engine) {
    sceneCamera = engine->getSceneCamera();
    editorCamera = engine->getEditorCamera();
    skybox = new SkyBox(cubeMapFaces);
}

RenderingEngine::~RenderingEngine() {
    if (skybox) delete skybox;
}

void RenderingEngine::render(SceneNode* scenenode) {
    skybox->render(sceneCamera->getProjectionMatrix(), sceneCamera->getViewMatrix());
}