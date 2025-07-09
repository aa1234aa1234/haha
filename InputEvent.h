//
// Created by D412 on 2025-07-07.
//
#pragma once
#ifndef INPUTEVENT_H
class InputEvent
{
    int key;
    glm::vec2 mousePos, mouseDelta;
    int eventType=-1;
public:
    InputEvent() {}
    InputEvent(int key, int eventType) : key(key), eventType(eventType) {}
    InputEvent(glm::vec2 mousePos, int eventType) : mousePos(mousePos), eventType(eventType) {}
    InputEvent(glm::vec2 mousePos, glm::vec2 mouseDelta, int eventType) : mousePos(mousePos), mouseDelta(mouseDelta), eventType(eventType) {}
    ~InputEvent() {}

    int getEventType() { return eventType; }
    glm::vec2 getMousePos() { return mousePos; }
    glm::vec2 getMouseDelta() { return mouseDelta; }
    int getKey() { return key; }
};
#define INPUTEVENT_H

#endif //INPUTEVENT_H
