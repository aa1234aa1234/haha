//
// Created by sw_306 on 2025-10-13.
//

#include "SkyBox.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

SkyBox::SkyBox(std::vector<std::string> faces) {
    texture = new Texture(faces);
    shader = new Shader();
}
