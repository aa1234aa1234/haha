//
// Created by sw_306 on 2025-10-29.
//

#ifndef PROJECT_PBRMATERIAL_H
#define PROJECT_PBRMATERIAL_H

#include "Material.h"

class Texture;
class Shader;

class PBRMaterial : public Material {
    Texture* albedoMap;
    Texture* metallicMap;
    Texture* roughnessMap;
    Texture* aoMap;

    glm::vec3 albedo;
    float metallic;
    float roughness;
    float ao;
public:
    PBRMaterial(const std::string& name);
    ~PBRMaterial();

    void UpdateUniforms(Shader& shader) override;

    Texture* getAlbedoMap() { return albedoMap; }
    Texture* getMetallicMap() { return metallicMap; }
    Texture* getRoughnessMap() { return roughnessMap; }
    Texture* getAOMap() { return aoMap; }

    glm::vec3 getAlbedo() { return albedo; }
    float getMetallic() { return metallic; }
    float getRoughness() { return roughness; }
    float getAO() { return ao; }

    void setAlbedoMap(Texture* tex) { albedoMap = tex; }
    void setMetallicMap(Texture* tex) { metallicMap = tex; }
    void setRoughnessMap(Texture* tex) { roughnessMap = tex; }
    void setAOMap(Texture* tex) { aoMap = tex; }

    void setAlbedo(glm::vec3 ad) { albedo = ad; }
    void setMetallic(float m) { metallic = m; }
    void setRoughness(float r) { roughness = r; }
    void setAO(float a) { ao = a; }
};


#endif //PROJECT_PBRMATERIAL_H