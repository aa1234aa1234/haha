//
// Created by sw_306 on 2025-10-13.
//

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H
#include "header.h"
#include <vector>

template<class VertexType>
class Mesh {
    std::vector<VertexType> vertices;
    std::vector<GLuint> indices;
    int instances = 1;
public:
    Mesh(std::vector<VertexType>& vertices, std::vector<GLuint>& indices, int instances);
};


#endif //PROJECT_MESH_H