#pragma once
#include "../header.h"
#include "../Shader.h"
#include <queue>

//extern UIContext* context;

class Engine;

struct UIElements {
	glm::vec2 position;
	glm::vec2 texcoord;
	glm::vec3 colors;
};

typedef struct Element {
	glm::vec2 position;;
	glm::vec3 color;
	glm::vec2 size;
	int id;
	glm::vec4 clipRect = glm::vec4(-1, -1, -1, -1);
};

using ComponentID = int32_t;

class UIComponent
{
protected:
	ComponentID componentId;
	void destroy();
	bool isDraggable = false;
	bool isVisible = true;
public:
	UIComponent* parentComponent;
	std::vector<UIComponent*> childComponents;
	Element uielement;
	glm::vec2 position;
	glm::vec3 size;
	UIComponent(const glm::vec2& pos, const glm::vec2& size);
	UIComponent();
	virtual ~UIComponent();

	static ComponentID generateID()
	{
		static ComponentID id = 0;
		return id++;
	}

	virtual void genVertices();
	virtual Element UpdateElement();
	virtual void render(Engine& engine);
	virtual int Update(glm::vec2 pos = glm::vec2());
	virtual void getUIElements(std::vector<Element>& v, std::vector<UIComponent*>& v1);
	void generateQuad(glm::vec3 color);
	void addChildComponent(UIComponent* child);
	int getComponentId() { return componentId; }
	virtual int onClick(glm::vec2 pos);
	virtual int onDrag(glm::vec2 pos, glm::vec2 pos2);
	virtual int onDoubleClick(glm::vec2 pos);
	bool Draggable() { return isDraggable; }
	bool Visible() { return isVisible; }
};

