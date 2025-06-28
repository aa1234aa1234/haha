//
// Created by sw_303 on 2025-06-28.
//

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "EventHandler.h"
#include <glm/glm.hpp>

class MouseEvent : public IEvent {
    enum MouseEventType
    {
        MOUSEDOWN,
        MOUSEUP,
        MOUSEMOVE
    };
    glm::vec2 mousePos, mouseOffset;
public:
    MouseEvent();
    ~MouseEvent();
    std::type_info getType() override
    {
        return typeid(MouseEventType);
    }
};



#endif //MOUSEEVENT_H
