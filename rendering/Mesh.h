//
// Created by sw_306 on 2025-10-13.
//

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H
#include "header.h"
#include <vector>
#include "Vertex.h"

class VertexArray;
class IndexBuffer;
class VertexBuffer;
class Shader;
class Material;

template<class VertexType>
class Mesh {
    std::string materialName;
    std::vector<VertexType> vertices;
    std::vector<GLuint> indices;
    int numInstances = 1;

    VertexArray* vao;
    IndexBuffer* ibo;
    VertexBuffer* vbo;

    std::vector<glm::mat4> instanceMatrices;
    VertexBuffer* instancevbo;

    void setUpMesh();
    void setUpInstanceAttrib();
public:
    Mesh(std::vector<VertexType>& vertices, std::vector<GLuint>& indices, int instances = 1);
    ~Mesh();

    void draw(Shader& shader, Material& material);
    void setMaterialName(const std::string& materialName);
    std::string getName() const { return materialName; }
};

#endif //PROJECT_MESH_H