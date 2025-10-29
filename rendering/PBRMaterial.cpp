//
// Created by sw_306 on 2025-10-29.
//

#include "PBRMaterial.h"

PBRMaterial::PBRMaterial() {

}

PBRMaterial::~PBRMaterial() {
    deleteTextures();
    if (albedoMap) delete albedoMap;
    if (metallicMap) delete metallicMap;
    if (roughnessMap) delete roughnessMap;
    if (aoMap) delete aoMap;
}
