//
// Created by user on 2026-03-12.
//

#ifndef CONSOLELOG_H
#define CONSOLELOG_H
#include "Entity.h"
#include "SystemCoordinator.h"
#include "Components.hpp"
#include <glm/glm.hpp>

class ConsoleLog : public Entity {
    SystemCoordinator* sc;
    std::vector<std::string>* log;
    float* offset;
    int* maxScroll;
    static const int LINEHEIGHT=20;
public:
    ConsoleLog(const glm::vec2& position, const glm::vec2& size) {
        sc = SystemCoordinator::getInstance();
        Initialize(position,size);
    }

    ~ConsoleLog() {
        if (log) delete log;
        if (offset) delete offset;
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        sc->RegisterEntity(this);
        sc->AddComponent(getId(), TransformComponent{position,glm::vec4(20,20,20,1), size});
        sc->AddComponent(getId(), ScrollableComponent{});
        sc->AddComponent(getId(), LogComponent{});
        log = &sc->GetComponent<LogComponent>(getId()).log;
        offset = &sc->GetComponent<ScrollableComponent>(getId()).offset;
        maxScroll = &sc->GetComponent<ScrollableComponent>(getId()).maxScroll;
    }

    void addLog(std::string& text, bool nextLine = false) { //subject to change
        if (!nextLine) (log->back()) += text;
        else
        {
            log->push_back(text);
            *maxScroll = LINEHEIGHT * log->size() - sc->GetComponent<TransformComponent>(getId()).size.y;
        }
    }

    glm::vec2 partitionLog() {
		//change this to incorporate offset
        if (offset == nullptr) return {};
        return glm::vec2((*offset)/LINEHEIGHT, ((*offset)+sc->GetComponent<TransformComponent>(getId()).size.y)/LINEHEIGHT);
    }
};

#endif //CONSOLELOG_H
