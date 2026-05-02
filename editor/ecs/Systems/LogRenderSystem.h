//
// Created by user on 2026-04-15.
//

#ifndef LOGRENDERSYSTEM_H
#define LOGRENDERSYSTEM_H
#include "Components.hpp"
#include "System.h"
#include "SystemCoordinator.h"
#include "VertexBuffer.h"
#include "TextHandler.h"
#include "ConsoleLog.h"

class LogRenderSystem : public System {
    SystemCoordinator* sc;
    const int ROW_HEIGHT = 20;

public:
    LogRenderSystem() {}
    ~LogRenderSystem() {}

    void Initialize() {
        sc = SystemCoordinator::getInstance();
        Signature signature;
        signature.set(sc->GetComponentType<TransformComponent>(), true);
        signature.set(sc->GetComponentType<LogComponent>(), true);
        sc->SetSystemSignature<LogRenderSystem>(signature);
    }

    void Update() {
		for(auto& p : entities) {
			auto transform = sc->GetComponent<TransformComponent>(p);
			auto logs = dynamic_cast<ConsoleLog*>(sc->GetEntity(p))->partitionLog();
			//std::string text = "i dont know what to put here";
			//Text t = Text{transform.position.x + 10, transform.position.y + 10, text};
			//TextHandler::getInstance()->manualDrawText(t, transform.position.x+transform.size.x, transform.position.y+transform.size.y, transform.position.x, transform.position.y);
			//std::cout << sc->GetComponent<ScrollableComponent>(p).offset << std::endl;
			//std::cout << "logtest";
			auto log = sc->GetComponent<LogComponent>(p);
			for (int i = logs.x,k=10; i<logs.y; i++,k+=ROW_HEIGHT)
			{
				Text t = Text{transform.position.x+10, transform.position.y+k, log.log[i]};
				TextHandler::getInstance()->manualDrawText(t, transform.position.x+transform.size.x, transform.position.y+transform.size.y, transform.position.x, transform.position.y);
			}
		}
    }
};

#endif //LOGRENDERSYSTEM_H
