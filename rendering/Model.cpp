//
// Created by sw_306 on 2025-10-29.
//

#include "Model.h"

#include "PBRMaterial.h"
#include "ResourceManager.h"
#include "Texture.h"


void Model::LoadModel(const std::string& path) {
    scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
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

Mesh<VertexPNTBUV> Model::processMesh(aiMesh* mesh) {
    std::vector<VertexPNTBUV> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;
    std::string matName;

    for (int i = 0; i<mesh->mNumVertices; i++) {
        VertexPNTBUV vertex{};
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->HasTangentsAndBitangents()) {
            vertex.tangent.x = mesh->mTangents[i].x;
            vertex.tangent.y = mesh->mTangents[i].y;
            vertex.tangent.z = mesh->mTangents[i].z;
            vertex.bitangent.x = mesh->mBitangents[i].x;
            vertex.bitangent.y = mesh->mBitangents[i].y;
            vertex.bitangent.z = mesh->mBitangents[i].z;
        }
        else {
            vertex.bitangent = glm::vec3();
            vertex.tangent = glm::vec3();
        }

        if (mesh->mTextureCoords[0]) {
            vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else {
            vertex.texCoord = glm::vec2();
        }
    }

    for (int i = 0; i<mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j<face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        matName = material->GetName().C_Str();

        if (material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0) {
            PBRMaterial pbr_material(matName);

            Texture* albedoMap;
            Texture* normalMap;
            Texture* metallicMap;
            Texture* roughnessMap;
            Texture* aoMap;

            albedoMap = loadTexture(material, aiTextureType_BASE_COLOR, Texture::TextureType::ALBEDO);
            normalMap = loadTexture(material, aiTextureType_NORMALS, Texture::TextureType::NORMAL);
            metallicMap = loadTexture(material, aiTextureType_METALNESS, Texture::TextureType::METALLIC);
            roughnessMap = loadTexture(material, aiTextureType_DIFFUSE_ROUGHNESS, Texture::TextureType::ROUGHNESS);
            aoMap = loadTexture(material, aiTextureType_AMBIENT_OCCLUSION, Texture::TextureType::AO);

            pbr_material.setAlbedoMap(albedoMap);
            pbr_material.setMetallicMap(metallicMap);
            pbr_material.setRoughnessMap(roughnessMap);
            pbr_material.setAOMap(aoMap);
            pbr_material.setNormalMap(normalMap);

            materials[matName] = pbr_material;
            ResourceManager::getInstance()->addMaterial(&pbr_material,matName);
            return Mesh<VertexPNTBUV>(vertices,indices, numInstances);
        }

        else {
            Material mat(matName);

            Texture* diffuseMap;
            Texture* specularMap;
            Texture* normalMap;

            aiColor4D aiColor[] = {{},{},{}};
            const char* key[] = {AI_MATKEY_COLOR_DIFFUSE, AI_MATKEY_COLOR_AMBIENT, AI_MATKEY_COLOR_SPECULAR};
            glm::vec4 color[3] = {{},{},{}};

            for (int i = 0; i<3; i++) {
                if (aiGetMaterialColor(material, key[i], 0, 0, &aiColor[i]) == AI_SUCCESS) {
                    color[i] = glm::vec4(aiColor[i].r, aiColor[i].g, aiColor[i].b, aiColor[i].a);
                }
            }

            diffuseMap = loadTexture(material, aiTextureType_DIFFUSE, Texture::TextureType::DIFFUSE);
            normalMap = loadTexture(material, aiTextureType_NORMALS, Texture::TextureType::NORMAL);
            specularMap = loadTexture(material, aiTextureType_SPECULAR, Texture::TextureType::SPECULAR);

            mat.setDiffuseMap(diffuseMap);
            mat.setSpecularMap(specularMap);
            mat.setNormalMap(normalMap);

            mat.setDiffuseColor(color[0]);
            mat.setAmbientColor(color[1]);
            mat.setSpecularColor(color[2]);

            materials[matName] = mat;
            ResourceManager::getInstance()->addMaterial(&mat, matName);
            return Mesh<VertexPNTBUV>(vertices,indices, numInstances);
        }
    }


}

Texture* Model::loadTexture(aiMaterial *mat, aiTextureType type, int typeName) {
    Texture* texture = nullptr;
    for (int i = 0; i<mat->GetTextureCount(type); i++) {
        aiString str;

        if (mat->GetTexture(type, i, &str) == AI_SUCCESS) {
            texture = ResourceManager::getInstance()->loadTexture(directory + '\\' + str.C_Str());
            texture->setType(typeName);
        }
    }
    return texture;
}
