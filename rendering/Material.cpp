//
// Created by sw_306 on 2025-10-27.
//

#include "Material.h"

#include "RenderingEngine.h"
#include "Texture.h"
#include "Shader.h"

void Material::deleteTextures() {
    delete specularMap;
    delete normalMap;
    delete diffuseMap;
}

void Material::UpdateUniforms(Shader &shader) {
    if (specularMap) {
        shader.SetUniform1i("material.useSpecular", 1);
        specularMap->bind(RenderingEngine::SamplerSlot::SPECULAR);
        shader.SetUniform1i("material.specularMap", RenderingEngine::SamplerSlot::SPECULAR);
    }
    else {
        shader.SetUniform1i("material.useSpecular", 0);
    }

    if (diffuseMap) {
        shader.SetUniform1i("material.useDiffuse", 1);
        diffuseMap->bind(RenderingEngine::SamplerSlot::DIFFUSE);
        shader.SetUniform1i("material.diffuseMap", RenderingEngine::SamplerSlot::DIFFUSE);
    }
    else {
        shader.SetUniform1i("material.useDiffuse", 0);
    }

    if (normalMap) {
        shader.SetUniform1i("material.useNormal", 1);
        normalMap->bind(RenderingEngine::SamplerSlot::NORMAL);
        shader.SetUniform1f("material.normalMap", RenderingEngine::SamplerSlot::NORMAL);
    }
    else {
        shader.SetUniform1i("material.useNormal", 0);
    }

    shader.SetUniform1f("material.shininess", shininess);
    shader.SetUniformVec4("material.specular", specularColor);
    shader.SetUniformVec4("material.diffuse", diffuseColor);
    shader.SetUniformVec4("material.ambient", ambientColor);
}

