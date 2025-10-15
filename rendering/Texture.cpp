//
// Created by sw_306 on 2025-10-13.
//

#include "Texture.h"

#include "stb/stb_image.h"

Texture::Texture() : renderId(0), target(GL_NONE) {}

Texture::Texture(std::string filePath) {

}

Texture::Texture(std::vector<std::string> faces) : renderId(0), width(0), height(0), target(GL_TEXTURE_CUBE_MAP) {
    stbi_set_flip_vertically_on_load(1);
    glGenTextures(1, &renderId);
    bind();
    int channels;
    for (int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "error when loading cubemap";
            stbi_image_free(data);
        }
    }
    setFiltering(GL_LINEAR,GL_LINEAR);
    setWrapping(GL_CLAMP_TO_EDGE);
    unbind();
    stbi_set_flip_vertically_on_load(0);
}

Texture::~Texture() {}

void Texture::initCubeMap(int width, int height) {
    if (!renderId) glGenTextures(1, &renderId);
    bind();
    this->width = width;
    this->height = height;
    for (int i = 0; i<6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    }
    setFiltering(GL_LINEAR,GL_LINEAR);
    setWrapping(GL_CLAMP_TO_EDGE);
    unbind();
}

void Texture::bind() {
    glBindTexture(target, renderId);
}

void Texture::unbind() {
    glBindTexture(target, 0);
}

void Texture::setWrapping(GLenum mode) {
    glTexParameteri(target, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, mode);
    if (target == GL_TEXTURE_CUBE_MAP) glTextureParameteri(target, GL_TEXTURE_WRAP_R, mode);
}

void Texture::setFiltering(GLenum minfilter, GLenum magfilter) {
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magfilter);
}
