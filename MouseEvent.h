//
// Created by sw_303 on 2025-06-28.
//

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "EventHandler.h"
#include <glm/glm.hpp>

class MouseEvent : public IEvent {
    std::string id = "MouseEvent";
    glm::vec2 mousePos, mouseOffset;
public:
    enum MouseEventType
    {
        MOUSEDOWN,
        MOUSEUP,
        MOUSEMOVE,
        MOUSEDRAG
    } eventType;

    MouseEvent() {}
    MouseEvent(glm::vec2 mousePos, glm::vec2 mouseOffset, MouseEventType eventType) : mousePos(mousePos), mouseOffset(mouseOffset), eventType(eventType) {}
    ~MouseEvent() {}
    const std::string& getId() override
    {
        return id;
    }

    std::type_index getType() override
    {
        return typeid(MouseEvent);
    }

    glm::vec2 getMousePos() { return mousePos; }
    glm::vec2 getMouseOffset() { return mouseOffset; }
    MouseEventType getEventType() { return eventType; }
};



#endif //MOUSEEVENT_H
