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

	static UIContext* instance;

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

	static UIContext* getInstance() {
		if (!instance) { return new UIContext(); }
		return instance;
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

