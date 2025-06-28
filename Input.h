//
// Created by sw_303 on 2025-06-21.
//

#ifndef INPUT_H
#define INPUT_H
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>


class Input {



    static Input* instance;
    glm::vec2 mousepos;
    glm::vec2 mousedelta;
    std::vector<char> keydown;
public:
    enum EventType
    {
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_MOVE,
        MOUSE_DRAG,
        KEY_DOWN,
    } eventType;
    Input();
    ~Input();

    static Input* getInstance()
    {
        if (!instance) return new Input();
        return instance;
    }

    std::vector<char> getKeyDown();
    glm::vec2 getMousePos();
    glm::vec2 getMouseDelta();
    void setMousePos(const float& x, const float& y);
    void setMouseDelta(const float& x, const float& y);
    void setKeyDown(const char& key);
    bool isKeyDown(const char& key);
    EventType getEventType() { return eventType; }
};



#endif //INPUT_H
