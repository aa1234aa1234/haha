#pragma once
#include "../header.h"
#include "UIComponent.h"

class Tab;

class TabView : public UIComponent {
	int TAB_NUM = 2;
	int TAB_WIDTH = 100, TAB_HEIGHT = 25;
	glm::vec3 color = glm::vec3(40, 40, 40);
	glm::vec2 mousedownpos = glm::vec2();
public:
	int selectedtab = 0;
	TabView() : UIComponent() {
		init();
	}
	TabView(const glm::vec2& pos, const glm::vec2& size) : UIComponent(pos,size) {
		/*parentComponent = nullptr;
		position.x = pos.x;
		position.y = pos.y;
		this->size.x = size.x;
		this->size.y = size.y;*/
		init();
	}
	~TabView() {
		destroy();
	}
	void init();
	int Update(glm::vec2 pos = glm::vec2()) override;
	int onClick(glm::vec2 pos) override;
	Element UpdateElement() override;
	int onDrag(glm::vec2 pos, glm::vec2 pos2) override;
	int onDoubleClick(glm::vec2 pos) override;
	void resize(glm::vec2 size);
	//Tab* getTab(int idx) { return dynamic_cast<Tab*>(childComponents[idx]); }
	UIComponent* getTab(int idx) { return childComponents[idx]; }
	void setPanelViewComponent(UIComponent* component);
};