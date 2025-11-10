//
// Created by sw_306 on 2025-10-13.
//

#include "Mesh.h"

#include "ErrorHandler.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Renderer.h"

template<class VertexType>
Mesh<VertexType>::Mesh(std::vector<VertexType> &vertices, std::vector<GLuint> &indices, int instances) {
    this->vertices = vertices;
    this->indices = indices;
    numInstances = instances;

    setUpMesh();
}

template<class VertexType>
void Mesh<VertexType>::setUpMesh() {
    vao = new VertexArray();
    vbo = new VertexBuffer(vertices.data(), vertices.size() * sizeof(VertexType));
    vao->addBuffer(*vbo, VertexType::getLayout());

    if (numInstances > 1) {
        setUpInstanceAttrib();
    }
    ibo = new IndexBuffer(indices.data(), indices.size());
}

template<class VertexType>
void Mesh<VertexType>::setUpInstanceAttrib() {
    vao->bind();
    vbo = new VertexBuffer(instanceMatrices.data(), instanceMatrices.size() * sizeof(glm::mat4));
    std::size_t offset = sizeof(glm::vec4);
    for (int i = 0; i<4; i++) {
        GLCall(glEnableVertexAttribArray(i+4));
        GLCall(glVertexAttribPointer(i+4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * offset)));
        GLCall(glVertexAttribDivisor(i+4, 1));
    }

}

template<class VertexType>
Mesh<VertexType>::~Mesh() {
    delete vbo;
    delete ibo;
    delete vao;
    if (instancevbo) delete instancevbo;
}

template<class VertexType>
void Mesh<VertexType>::draw(Shader& shader, Material& material) {
    material.UpdateUniforms(shader);

    Renderer::getInstance()->draw(*vao, *ibo, shader, numInstances);
}

template<class VertexType>
void Mesh<VertexType>::setMaterialName(const std::string& materialName) {
    this->materialName = materialName;
}

template Mesh<VertexPNTBUV>::Mesh(std::vector<VertexPNTBUV>& vertices, std::vector<GLuint>& indices, int instances);
template Mesh<VertexPNTBUV>::~Mesh();
template void Mesh<VertexPNTBUV>::setMaterialName(const std::string& materialName);
template void Mesh<VertexPNTBUV>::draw(Shader& shader, Material& material);

template Mesh<VertexPNUV>::Mesh(std::vector<VertexPNUV>& vertices, std::vector<GLuint>& indices, int instances);
template Mesh<VertexPNUV>::~Mesh();
template void Mesh<VertexPNUV>::setMaterialName(const std::string& materialName);
template void Mesh<VertexPNUV>::draw(Shader& shader, Material& material);

