//
// Created by sw_306 on 2025-10-29.
//

#include "PBRMaterial.h"

#include "RenderingEngine.h"
#include "Shader.h"
#include "Texture.h"

PBRMaterial::PBRMaterial(const std::string& name) : Material(name) {
}

PBRMaterial::~PBRMaterial() {
    deleteTextures();
    if (albedoMap) delete albedoMap;
    if (metallicMap) delete metallicMap;
    if (roughnessMap) delete roughnessMap;
    if (aoMap) delete aoMap;
}

void PBRMaterial::UpdateUniforms(Shader &shader) {
    shader.SetUniform1i("use_pbr", 1);

    shader.SetUniformVec3("pbr_material.albedo", albedo);
    shader.SetUniform1f("pbr_material.metallic", metallic);
    shader.SetUniform1f("pbr_material.roughness", roughness);
    shader.SetUniform1f("pbr_material.ao", ao);

    if (albedoMap) {
        shader.SetUniform1i("pbr_material.useAlbedo", 1);
        albedoMap->bind(RenderingEngine::SamplerSlot::ALBEDO);
        shader.SetUniform1i("pbr_material.albedoMap", RenderingEngine::SamplerSlot::ALBEDO);
    }
    else {
        shader.SetUniform1i("pbr_material.useAlbedo", 0);
    }

    if (normalMap) {
        shader.SetUniform1i("pbr_material.useNormal", 1);
        normalMap->bind(RenderingEngine::SamplerSlot::NORMAL);
    }
    else {
        shader.SetUniform1i("pbr_material.useNormal", 0);
    }

    if (metallicMap) {
        shader.SetUniform1i("pbr_material.useMetallic", 1);
        metallicMap->bind(RenderingEngine::SamplerSlot::METALLIC);
    }
    else {
        shader.SetUniform1i("pbr_material.useMetallic", 0);
    }

    if (roughnessMap) {
        shader.SetUniform1i("pbr_material.useRoughness", 1);
        roughnessMap->bind(RenderingEngine::SamplerSlot::ROUGHNESS);
    }
    else {
        shader.SetUniform1i("pbr_material.useRoughness", 0);
    }
}

