//
// Created by sw_306 on 2025-10-13.
//

#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H
#include "header.h"


class Texture {
    GLuint target;
    std::string filePath;
    unsigned int renderId;
    int width, height;
public:
    Texture();
    Texture(std::string filePath);
    //for cube maps
    Texture(std::vector<std::string> faces);
    ~Texture();

    void bind();
    void unbind();

    void initCubeMap(int width, int height);
    void setWrapping(GLenum mode);
    void setFiltering(GLenum minfilter, GLenum magfilter);
};


#endif //PROJECT_TEXTURE_H