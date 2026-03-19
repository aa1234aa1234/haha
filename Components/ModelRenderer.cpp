//
// Created by user on 2026-03-19.
//

#include "ModelRenderer.h"
#include "Shader.h"
#include "SceneNode.h"
#include "CameraComponent.h"
#include "Model.h"
#include "ResourceManager.h"

void ModelRenderer::render(Shader* shader, CameraComponent* camera) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, parent->getTransform().getTranslation());
    model = glm::scale(model, parent->getTransform().getScale());
    shader->SetUniformMat4f("model", model);
    shader->SetUniformMat4f("view", camera->getViewMatrix());
    shader->SetUniformMat4f("projection", camera->getProjectionMatrix());
    this->model->draw(*shader);
}
