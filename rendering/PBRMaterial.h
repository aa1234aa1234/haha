//
// Created by sw_306 on 2025-10-29.
//

#ifndef PROJECT_PBRMATERIAL_H
#define PROJECT_PBRMATERIAL_H

#include "Material.h"

class Texture;

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
    PBRMaterial();
    ~PBRMaterial();
};


#endif //PROJECT_PBRMATERIAL_H