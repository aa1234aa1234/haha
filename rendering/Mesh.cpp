//
// Created by sw_306 on 2025-10-13.
//

#include "Mesh.h"

#include "ErrorHandler.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TestMesh.h"

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
    vao->addBuffer(*vbo, VertexType::getVertexLayout());

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
void Mesh<VertexType>::draw(Shader& shader) {

}

template<class VertexType>
void Mesh<VertexType>::setMaterialIndex(int materialIndex) {
    this->materialIndex = materialIndex;
}

