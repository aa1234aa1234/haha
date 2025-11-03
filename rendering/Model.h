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
#include "Mesh.h"
#include <assimp/postprocess.h>

#include "Texture.h"

class Material;
class Texture;

class Model {
    //this can wait for now
    std::string directory;
    std::string fileName;
    std::vector<Mesh<VertexPNTBUV>> meshes;
    std::map<std::string, Material> materials;

    Assimp::Importer importer;
    const aiScene* scene=nullptr;

    int numInstances = 1;
public:
    Model(const char* directory, const char* fileName, int numInstances = 1) : directory(directory), fileName(fileName), numInstances(numInstances) {}
    ~Model() {
        if (scene) delete scene;
    }

    void LoadModel(const std::string& path);
    void processNode(aiNode* node);
    Mesh<VertexPNTBUV> processMesh(aiMesh* mesh);
    Texture* loadTexture(aiMaterial* mat, aiTextureType type, int typeName);
};


#endif //PROJECT_MODEL_H