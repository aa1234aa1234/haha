//
// Created by sw_303 on 2025-06-21.
//

#ifndef DOCKSPACE_H
#define DOCKSPACE_H
#include "FrameBuffer.h"
#include "header.h"
#include "Shader.h"
#include "UIComponent.h"


class FrameBuffer;
class Shader;

class DockSpace {
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0,
        };
    unsigned int vao, vbo, quadvao, quadvbo;
    const char* vertex = R"(
    #version 330 core

    layout(location = 0) in vec2 position;
    layout(location = 1) in vec4 acolor;

    out vec2 pos;
    out vec4 colors;

    void main() {
        gl_Position = vec4(position, 1.0);
        colors = acolor;
        pos = position;
    }
    )";

    const char* frag = R"(
    #version 330 core

    layout (location = 0) out vec4 fragColor;

    in vec4 colors;
    in vec2 pos;

	vec4 NormalizeRGB(vec4 color) {
		return vec4(color.xyz/255.0,color.a);
	}

    void main() {
        if (colors.a != 0.0) fragColor = colors; else fragColor = vec4(1.0,1.0,1.0,0.0);
    }
    )";

    struct OverlayElement {
        glm::vec2 pos;
        glm::vec4 color;
    };
public:
	Shader* shader;
	FrameBuffer* frameBuffer;
	std::vector<OverlayElement> buffer;
	std::vector<UIComponent*> uiComponents;
	int buffersize = 0;

	DockSpace(const int& width, const int& height);

    ~DockSpace() {
		delete frameBuffer;
		delete shader;
		if (vao) {
			glDeleteVertexArrays(1, &vao);
		}

		if (vbo) {
			glDeleteBuffers(1, &vbo);
		}
		if (quadvao) {
			glDeleteVertexArrays(1, &quadvao);
		}

		if (quadvbo) {
			glDeleteBuffers(1, &quadvbo);
		}
	}

	void Initialize() {
		int i = buffer.size() - 1;
		buffer.reserve(buffer.size() + 6 * 5);
		buffer[i + 1] = {};
	}

	unsigned int getBufferTexture() {
		return frameBuffer->getFrameTexture();
	}

	void end();
	void render();
};



#endif //DOCKSPACE_H
