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
    }

    void addLog(std::string& text) {
        log->push_back(text);
    }

    void partitionLog() {
        
    }
};

#endif //CONSOLELOG_H
