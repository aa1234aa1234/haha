//
// Created by sw_303 on 2025-11-15.
//

#ifndef MESHUTILS_H
#define MESHUTILS_H
#include <vector>

#include "glad/gl.h"

template<class Vertex>
class Mesh;

class MeshUtils
{
public:
    template<class Vertex>
    static void CubeMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f, -1.0f)});
        vertices.push_back(Vertex{glm::vec3(1.0f, -1.0f,  1.0f)});
        vertices.push_back(Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)});

        indices = {
            0, 1, 2,
            2, 3, 0,
        // BACK
            4, 5, 6,
            6, 7, 4,
        // UP
            8, 9, 10,
            10, 11, 8,
        // DOWN
            12, 13, 14,
            14, 15, 12,
        // LEFT
            16, 17, 18,
            18, 19, 16,
        // RIGHT
            20, 21, 22,
            22, 23, 20
        };
    }
};

#endif //MESHUTILS_H
