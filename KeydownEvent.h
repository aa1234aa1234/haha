//
// Created by D412 on 2025-06-30.
//

#ifndef KEYDOWNEVENT_H
#define KEYDOWNEVENT_H
#include "EventHandler.h"


class KeydownEvent : public IEvent{
    std::string id = "KeyDownEvent";
    enum KeyDown
    {
        KEY_DOWN = 4
    } eventType;
    int pressedkey = 0;
public:
    KeydownEvent(int keycode) {}
    const std::string& getId() override
    {
        return id;
    }
    std::type_index getType() override
    {
        return typeid(KeydownEvent);
    }
    int getKeycode() { return pressedkey; }
    int getEventType() { return eventType; }
};



#endif //KEYDOWNEVENT_H
