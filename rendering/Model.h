//
// Created by sw_306 on 2025-10-29.
//

#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H
#include "header.h"
#include <map>
#include "Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh;
class Material;

class Model {
    //this can wait for now
    std::string directory;
    std::string fileName;
    std::vector<Mesh<VertexPNTBUV>> meshes;
    std::map<int, Material*> materials;

    Assimp::Importer importer;
    const aiScene* scene=nullptr;
public:
    Model() {}
    ~Model() {}

    void LoadModel(const std::string& path);
    void processNode(aiNode* node);
    void processMesh(aiMesh* mesh);
};


#endif //PROJECT_MODEL_H