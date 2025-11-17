//
// Created by sw_306 on 2025-11-03.
//

#include "ResourceManager.h"
#include "rendering/Material.h"
#include "rendering/Texture.h"

ResourceManager* ResourceManager::instance = nullptr;

void ResourceManager::destroy() {
    for (auto& p : materials) {
        delete p.second;
    }
    materials.clear();
    for (auto& p : textures) {
        delete p.second;
    }
    textures.clear();
}

Material* ResourceManager::getMaterialByName(const std::string &name) {
    if (materials.find(name) == materials.end()) {
        //add a logger system here
        return nullptr;
    }
    return materials[name];
}

void ResourceManager::addMaterial(Material* material, const std::string& name) {
    std::string name1 = name;
    if (getMaterialByName(name) != nullptr) {
        name1 += " (1)";
    }
    materials[name1] = material;
}

Texture* ResourceManager::loadTexture(const std::string& filepath) {
    textures[filepath] = new Texture(filepath);
}
