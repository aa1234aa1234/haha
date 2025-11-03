//
// Created by sw_306 on 2025-11-03.
//

#include "ResourceManager.h"
#include "rendering/Material.h"
#include "rendering/Texture.h"

ResourceManager* ResourceManager::instance = nullptr;

Material* ResourceManager::getMaterialByName(const std::string &name) {
    if (materials.find(name) == materials.end()) {
        //add a logger system here
        return nullptr;
    }
    return materials[name];
}

void ResourceManager::addMaterial(Material* material, std::string& name) {

    if (getMaterialByName(name) == nullptr) {
        name += " (1)";
    }
    materials[name] = material;
}

Texture* ResourceManager::loadTexture(const std::string& filepath) {
    textures[filepath] = new Texture(filepath);
}
