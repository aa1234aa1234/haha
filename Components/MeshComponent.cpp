//
// Created by sw_306 on 2025-11-12.
//

#include "MeshComponent.h"

#include "Vertex.h"
#include "Mesh.h"
#include "SceneNode.h"
#include "Shader.h"

template <class VertexType>
void MeshComponent<VertexType>::render(Shader* shader, CameraComponent* camera)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, parent->getTransform().getTranslation());
    model = glm::scale(model, parent->getTransform().getScale());
    shader->SetUniformMat4f("model", model);
    _mesh->draw(shader, *material);
}

template void MeshComponent<VertexPNTBUV>::render(Shader* shader, CameraComponent* camera);
