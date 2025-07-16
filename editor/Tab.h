#pragma once
#include "header.h"
#include "UIComponent.h"
#include "TabView.h"
#include "TextHandler.h"

//extern TextHandler* textHandler;

class Tab : public UIComponent {
	std::string title;
	int id = 0, textidx, activeComponentId = -1;
	bool active = 0;
	UIComponent* viewComponent=nullptr;
	glm::vec3* color = new glm::vec3[2]{ glm::vec3(40,40,40),glm::vec3(60,60,60) };;
	template<typename T, typename K>
	inline bool instanceof(const K& k) {
		return typeid(T).hash_code() == typeid(k).hash_code();
	}
public:
	Tab(const glm::vec2& pos, const glm::vec2& size, const int& id, const char* title) : UIComponent(pos, size) {
		this->id = id;
		this->title = std::string(title);
		uielement = { position,color[active],size,1 };
		textidx = TextHandler::getInstance()->addText(position.x+5, position.y+2, this->title);
	}
	Tab() : UIComponent() {}
	~Tab() {
		destroy();
		delete color;
	}
	int getActiveComponent() { return activeComponentId; }
	Element UpdateElement() override;
	int Update(glm::vec2 pos) override;
	int onClick(glm::vec2 pos) override;
	void setActive(int a) { active = a; }
	void setViewComponent(UIComponent* t) { viewComponent = t; }
	UIComponent* getViewComponent() { return viewComponent; }
};
