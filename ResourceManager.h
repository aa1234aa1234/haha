//
// Created by sw_306 on 2025-11-03.
//

#ifndef PROJECT_RESOURCEMANAGER_H
#define PROJECT_RESOURCEMANAGER_H

#include <map>
#include <string>

class Material;
class Texture;


class ResourceManager {
    static ResourceManager* instance;
    std::map<std::string, Material*> materials;
    std::map<std::string, Texture*> textures;
public:
    ResourceManager() {}
    ~ResourceManager() {
        delete instance;
    }

    static ResourceManager* getInstance() {
        if (!instance) instance = new ResourceManager();
        return instance;
    }

    Material* getMaterialByName(const std::string& name);
    void addMaterial(Material* material, std::string& name);
    Texture* loadTexture(const std::string& filepath);
};


#endif //PROJECT_RESOURCEMANAGER_H