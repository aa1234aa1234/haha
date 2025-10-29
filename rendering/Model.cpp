//
// Created by sw_306 on 2025-10-29.
//

#include "Model.h"

Model::Model() {

}

Model::~Model() {

}

void Model::LoadModel(const std::string& path) {
    scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    fileName = path.substr(path.find_last_of('/') + 1, path.length());
    processNode(scene->mRootNode);
}

void Model::processNode(aiNode* node) {
    for (int i = 0; i<node->mNumMeshes; i++) {
        processMesh(scene->mMeshes[node->mMeshes[i]]);
    }

    for (int i = 0; i<node->mNumChildren; i++) {
        processNode(node->mChildren[i]);
    }
}

void Model::processMesh(aiMesh* mesh) {
    std::vector<VertexPNTBUV> vertices;
    std::vector<unsigned int> indices;

}