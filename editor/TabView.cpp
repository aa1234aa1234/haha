#include "TabView.h"

#include "Engine.h"
#include "Panel.h"
#include "SceneView.h"
#include "Tab.h"

void TabView::init() {
	isDraggable = true;
	const char* a[] = { "Game","Scene" };
	for (int i = 0; i < TAB_NUM; i++) {
		addChildComponent(new Tab(glm::vec2(position.x + TAB_WIDTH * i, position.y), glm::vec2(TAB_WIDTH, TAB_HEIGHT), i, a[i]));
	}
	uielement = { position,color,size,0 };
	addChildComponent(new Panel<SceneView>(glm::vec2(position.x,position.y+size.y), glm::vec2(size.x,Engine::getScreenHeight()-size.y),nullptr));
}

int TabView::Update(glm::vec2 pos) {
	for (int i = 0; i < TAB_NUM; i++) {
		if (i != selectedtab) dynamic_cast<Tab*>(childComponents[i])->setActive(0);
		else {
			dynamic_cast<Panel<SceneView>*>(childComponents[TAB_NUM])->changeViewComponent(dynamic_cast<Tab*>(childComponents[i])->getViewComponent());
		}
	}
	
	UIComponent::Update();
	std::cout << childComponents[childComponents.size() - 1]->getComponentId() << std::endl;
	return childComponents[childComponents.size()-1]->getComponentId();
}

Element TabView::UpdateElement() {
	uielement = { position,color,size, 0};
	for (auto& p : childComponents) p->UpdateElement();
	return uielement;
}

int TabView::onClick(glm::vec2 pos) {
	mousedownpos = pos - position;;
	return getComponentId();
}

int TabView::onDrag(glm::vec2 pos, glm::vec2 pos2) {
	//std::cout << "drag" << std::endl;
	position = position + (pos - pos2);
	UIComponent::Update(pos-pos2);
	return childComponents[childComponents.size()-1]->getComponentId();
}

void TabView::resize(glm::vec2 size) {
	this->size.x = 1700;
	(*(childComponents.end() - 1))->size = glm::vec3(size.x,size.y,0);
	UIComponent::Update();
}

int TabView::onDoubleClick(glm::vec2 pos) {
	
	resize(glm::vec2(1700, 900));
	return childComponents[childComponents.size() - 1]->getComponentId();
}

void TabView::setPanelViewComponent(UIComponent* component)
{
	for (int i = 0; i<TAB_NUM; i++)
	{
		dynamic_cast<Tab*>(childComponents[i])->setViewComponent(component);
	}
}
