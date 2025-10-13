//
// Created by sw_306 on 2025-09-22.
//

#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H
#include <glm/glm.hpp>

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
    static Renderer* instance;
public:

    void clearScreen();
    void clearColor(const glm::vec4& color);

    //renderer doesnt actually hold any data initialization order doesnt matter
    static Renderer* getInstance() {
        if (!instance) instance = new Renderer();
        return instance;
    }

    void draw(VertexArray& vao, IndexBuffer& index, Shader& shader, int instances = 1);
};


#endif //PROJECT_RENDERER_H