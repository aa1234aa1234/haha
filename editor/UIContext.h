#pragma once
#include "header.h"
#include "UIComponent.h"
#include <map>

#include "DockSpace.h"
#include "EventHandler.h"
#include "Adapter.h"
#include "FrameBuffer.h"
#define MAX_COMPONENTS 10000


class Engine;

class UIContext
{

	struct UpdateBatch
	{
		int start,end;
	};

	enum State {
		IDLE,
		CLICK,
		DRAG
	} state;

	static UIContext* instance;

	std::vector<UIComponent*> rootComponents;
	std::vector<UIComponent*> instanceData;
	std::vector<Element> dataBuffer;
	std::vector<UpdateBatch> updateBatches;
	Shader* shader;
	//LayoutOverlay* overlayElement;
	DockSpace* dockspace;
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
		if (dockspace != nullptr) delete dockspace;
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
		if (!instance) { instance = new UIContext(); }
		return instance;
	}

	static void destroyInstance()
	{
		delete instance;
		instance = nullptr;
	}

	void init(int width, int height);
	void add(UIComponent* component);
	void setup();
	void setSize(int& width, int& height);
	void DrawComponents(Engine& engine);
	void pack();
	void onClick(glm::vec2 pos);
	void onDrag(glm::vec2 pos, glm::vec2 pos2);
	void onRelease(glm::vec2 pos);
	void onDoubleClick(glm::vec2 pos);
	void onUpdate(int start, int end);
	void update();
	UIComponent* getComponent(int id) { return instanceData[id]; }
};


