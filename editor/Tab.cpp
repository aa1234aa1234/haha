#include "Tab.h"

int Tab::onClick(glm::vec2 pos) {
	if (parentComponent == nullptr) return -1;
	active = true;
	if (instanceof<TabView*>(parentComponent)) {
		dynamic_cast<TabView*>(parentComponent)->selectedtab = id;
		
		return parentComponent->Update();
		//return UIComponent::onClick();
	}
	else {
		
		dynamic_cast<TabView*>(parentComponent)->selectedtab = id;
		
		return parentComponent->Update();
		//return componentId;
	}
}

Element Tab::DrawComponent() {
	uielement = { position,color[active],size,1 };
	//textHandler->draw(position.x, position.y, title);
	return uielement;
}

int Tab::Update(glm::vec2 pos) {
	uielement = { position,color[active],size,1 };
	textHandler->editText(position.x + 5, position.y + 2, title, textidx);
	//return UIComponent::Update();
	return componentId;
}