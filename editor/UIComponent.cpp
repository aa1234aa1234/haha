#include "UIComponent.h"

void UIComponent::destroy() {
    for (auto& p : childComponents) {
        delete p;
    }
    childComponents.clear();
    //if(parentComponent != nullptr) delete parentComponent;
}

UIComponent::UIComponent(const glm::vec2& pos, const glm::vec2& size) : parentComponent(nullptr) {
	position.x = pos.x;
	position.y = pos.y;
    this->size.x = size.x;
    this->size.y = size.y;
	genVertices();
}

UIComponent::UIComponent() : parentComponent(nullptr) {
}

UIComponent::~UIComponent() {
    destroy();
}

void UIComponent::genVertices() {
    //generateQuad();
}


void UIComponent::generateQuad(glm::vec3 color) {
    /*float ndc[] = { 1.0, 1.0 ,1.0,1.0 ,1.0,-1.0, 1.0,-1.0, -1.0,1.0, -1.0,1.0, -1.0,-1.0, -1.0,-1.0, 1.0,-1.0, 1.0,-1.0, -1.0,1.0,-1.0,1.0 };
    for (int i = 0; i < 24; i+=4) {
        uielements.push_back({ glm::vec2(ndc[i],ndc[i + 1]), glm::vec2(ndc[i + 2],ndc[i + 3]), color });
    }*/
    /*
    uielements.push_back({ glm::vec2(1.0,1.0),   glm::vec2(1.0,1.0),    glm::vec3(0.45, 0.45, 0.45) });
    uielements.push_back({ glm::vec2(1.0,-1.0),  glm::vec2(1.0,-1.0),   glm::vec3(0.45, 0.45, 0.45) });
    uielements.push_back({ glm::vec2(-1.0,1.0),  glm::vec2(-1.0,1.0),   glm::vec3(0.45, 0.45, 0.45) });
    uielements.push_back({ glm::vec2(-1.0,-1.0), glm::vec2(-1.0,-1.0),  glm::vec3(0.45, 0.45, 0.45) });
    uielements.push_back({ glm::vec2(1.0,-1.0),  glm::vec2(1.0,-1.0),   glm::vec3(0.45, 0.45, 0.45) });
    uielements.push_back({ glm::vec2(-1.0,1.0),  glm::vec2(-1.0,1.0),   glm::vec3(0.45, 0.45, 0.45) });*/
}

Element UIComponent::DrawComponent() {
    return uielement;
}

int UIComponent::Update(glm::vec2 pos) {
    if (parentComponent == nullptr) {
        for (auto& p : childComponents) {
            p->position = p->position + pos;
            p->Update();
        }
    }
    DrawComponent();
    return 0;
}

void UIComponent::addChildComponent(UIComponent* child) {
    child->parentComponent = this;
    childComponents.reserve(childComponents.size() + 1);
    childComponents.emplace_back(child);
}

int UIComponent::onClick(glm::vec2 pos) {
    UIComponent* par = parentComponent;
    while (par != nullptr) {
        par = par->parentComponent;
    }
    return componentId;
}

int UIComponent::onDrag(glm::vec2 pos, glm::vec2 pos2) {
    return componentId;
}

int UIComponent::onDoubleClick(glm::vec2 pos) {
    return componentId;
}

void UIComponent::getUIElements(std::vector<Element>& v, std::vector<UIComponent*>& v1) {

    std::queue<UIComponent*> q;
    q.push(this);
    while (q.size()) {
        UIComponent* a = q.front();
        q.pop();
        for (auto& p : a->childComponents) {
            q.push(p);
        }
        a->componentId = v.size();
        v.push_back(a->uielement);
        v1.reserve(v1.size() + 1);
        v1.emplace_back(a);
    }
}