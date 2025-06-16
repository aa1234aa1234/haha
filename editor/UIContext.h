#pragma once
#include "../header.h"
#include "UIComponent.h"
#include <map>
#include "../EventHandler.h"
#include "../Adapter.h"
#include "../FrameBuffer.h"
#define MAX_COMPONENTS 10000






class UIContext : public Adapter
{
	
	enum State {
		IDLE,
		CLICK,
		DRAG
	} state;

	class LayoutOverlay {
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
		int buffersize = 0;

		LayoutOverlay(int& width, int& height) {
			frameBuffer = new FrameBuffer(width, height);
			shader = new Shader();
			shader->createFromSource(std::string(vertex), std::string(frag));
			glGenBuffers(1, &vbo);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glGenBuffers(1, &quadvbo);
			glGenVertexArrays(1, &quadvao);
			glBindVertexArray(quadvao);
			glBindBuffer(GL_ARRAY_BUFFER, quadvbo);
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ndc, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		~LayoutOverlay() {
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

		void end() {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			

			glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(OverlayElement), NULL, GL_DYNAMIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, buffer.size() * sizeof(OverlayElement), buffer.data());
			buffersize = buffer.size();
			buffer.clear();
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void render() {
			shader->use();
			glBindVertexArray(vao);
			glLineWidth(3.0f);
			glDrawElements(GL_LINES, buffersize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(quadvao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	};

	std::vector<UIComponent*> rootComponents;
	std::vector<UIComponent*> instanceData;
	std::vector<Element> dataBuffer;
	Shader* shader;
	//LayoutOverlay* overlayElement;
	unsigned int vao,vbo,instancevbo;
	int width, height;
	int targetId = -5000;
	int findComponent(glm::vec2 pos);

public:
	UIContext();
	~UIContext() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &instancevbo);
		delete shader;
		//delete overlayElement;
		for (auto& p : rootComponents) {
			delete p;
		}
		rootComponents.clear();
		for (auto& p : instanceData) {
			//delete p;
		}
		instanceData.clear();
	}
	void init(int width, int height);
	void add(UIComponent* component);
	void setup();
	void setSize(int& width, int& height);
	void DrawComponents();
	void pack();
	void onClick(glm::vec2 pos) override;
	void onDrag(glm::vec2 pos, glm::vec2 pos2) override;
	void onRelease(glm::vec2 pos) override;
	void onDoubleClick(glm::vec2 pos) override;
	void onUpdate(int start, int end) override;
};

