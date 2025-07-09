//
// Created by D412 on 2025-07-09.
//

#include "Container.h"
#include "Panel.h"
#include "SceneView.h"
#include "Tab.h"

void Container::init() {
    isDraggable = true;
    const char* a[] = { "Game","Scene" };
    for (int i = 0; i < TAB_NUM; i++) {
        addChildComponent(new Tab(glm::vec2(position.x + TAB_WIDTH * i, position.y), glm::vec2(TAB_WIDTH, TAB_HEIGHT), i, a[i]));
    }
    uielement = { position,color,size,0 };
    addChildComponent(new Panel<SceneView>(glm::vec2(position.x,position.y+size.y), glm::vec2(size.x,450),nullptr));
}

int Container::Update(glm::vec2 pos) {
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

Element Container::DrawComponent() {
    uielement = { position,color,size, 0};
    for (auto& p : childComponents) p->DrawComponent();
    return uielement;
}

int Container::onClick(glm::vec2 pos) {
    mousedownpos = pos - position;;
    return getComponentId();
}

int Container::onDrag(glm::vec2 pos, glm::vec2 pos2) {
    //std::cout << "drag" << std::endl;
    position = position + (pos - pos2);
    UIComponent::Update(pos-pos2);
    return childComponents[childComponents.size()-1]->getComponentId();
}

void Container::resize(glm::vec2 size) {
    this->size.x = size.x;
    this->size.y = size.y;
    (*(childComponents.end() - 1))->size = glm::vec3(size.x,size.y,0);
    UIComponent::Update();
}

int Container::onDoubleClick(glm::vec2 pos) {

    resize(glm::vec2(1700,900));
    return childComponents[childComponents.size() - 1]->getComponentId();
}

void Container::setPanelViewComponent(UIComponent* component)
{
    for (int i = 0; i<TAB_NUM; i++)
    {
        dynamic_cast<Tab*>(childComponents[i])->setViewComponent(component);
    }
}

