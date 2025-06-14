#include "header.h"
#include "UIComponent.h"

#pragma once
template<class T>
class Panel : public UIComponent
{
	static_assert(std::is_base_of<UIComponent, T>::value, "type must be UIComponent");
	T* viewComponent;
public:
	Panel() : UIComponent() {}
	Panel(const glm::vec2& pos, const glm::vec2& size, T* component) : UIComponent(pos, size) {
		viewComponent = component;
		uielement = { position, glm::vec3(0,0,0), size, 2 };
	}
	~Panel() {
		destroy();
		delete viewComponent;
	}

	Element DrawComponent() override {
		if (viewComponent != nullptr) {
			viewComponent->renderScene();
			glBindTexture(GL_TEXTURE_2D, viewComponent->getSceneTexture());
		}
		return uielement;
	}

	int onClick(glm::vec2 pos) override {
		if (viewComponent == nullptr) return -1;
		viewComponent->onClick(pos);
		return getComponentId();
	}

	int onDrag(glm::vec2 pos, glm::vec2 pos2) override {
		if (viewComponent == nullptr) return -1;
		return viewComponent->onDrag(pos, pos2);
	}

	int Update(glm::vec2 pos = glm::vec2()) override {
		DrawComponent();
		
		uielement = { position, glm::vec3(0,0,0), size, 2 };
		
		return getComponentId();
	}

	void changeViewComponent(UIComponent* viewcomponent) {
		if (viewcomponent != nullptr) {
			viewComponent = dynamic_cast<T*>(viewcomponent);
		}
		else viewComponent = nullptr;
	}
};

