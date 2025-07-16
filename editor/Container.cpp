//
// Created by D412 on 2025-07-09.
//

#include "Container.h"
#include "Panel.h"
#include "SceneView.h"
#include "Tab.h"
#include "UIContext.h"

void Container::init() {
    isDraggable = true;
    clipRect = glm::vec4(position.x, position.y+TAB_HEIGHT, size.x, size.y-TAB_HEIGHT);
}


int Container::Update(glm::vec2 pos) {
    for (int i = 0; i < TAB_NUM; i++) {
        if (i != selectedtab) dynamic_cast<Tab*>(childComponents[i])->setActive(0);
    }

    UIComponent::Update();
    std::cout << childComponents[childComponents.size() - 1]->getComponentId() << std::endl;
    return childComponents[childComponents.size()-1]->getComponentId();
}

Element Container::UpdateElement() {
    uielement = { position,color,size, 0};
    for (auto& p : childComponents) p->UpdateElement();
    return uielement;
}

int Container::onClick(glm::vec2 pos) {
    mousedownpos = pos - position;;
    return getComponentId();
}

int Container::onDrag(glm::vec2 pos, glm::vec2 pos2) {
    //std::cout << "drag" << std::endl;
    position = position + (pos - pos2);
    clipRect.x = position.x;
    clipRect.y = position.y+TAB_HEIGHT;
    UIComponent::Update(pos-pos2);
    return childComponents[childComponents.size()-1]->getComponentId();
}

void Container::addTab(Tab* tab)
{
    addChildComponent(tab);
    TAB_NUM++;
    UIContext::getInstance()->getComponent(tab->getActiveComponent())->uielement.clipRect = this->clipRect;
    UIContext::getInstance()->getComponent(tab->getActiveComponent())->uielement.position = glm::vec2(clipRect.x, clipRect.y);
};

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

