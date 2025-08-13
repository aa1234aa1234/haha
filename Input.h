
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
    double xoffset, yoffset;
    std::unordered_map<char,bool> keydown;
    int eventType=-1;
public:
    enum EventType
    {
        MOUSE_DOWN=0,
        MOUSE_UP,
        MOUSE_MOVE,
        MOUSE_DRAG,
        KEY_DOWN,
        KEY_UP,
        SCROLL
    };
    Input();
    ~Input();

    static Input* getInstance()
    {
        if (!instance) instance = new Input();
        return instance;
    }

    std::unordered_map<char,bool> getKeyDown();
    glm::vec2 getMousePos();
    glm::vec2 getMouseDelta();
    void setMousePos(const float& x, const float& y);
    void setMouseDelta(const float& x, const float& y);
    void setMousePos(glm::vec2 pos) { mousepos = pos; }
    void setMouseDelta(glm::vec2 delta) { mousedelta = delta; }
    void setKeyDown(const char& key, bool down);
    bool isKeyDown(const char& key);
    void setXOffset(const double& x) { xoffset = x; }
    void setYOffset(const double& y) { yoffset = y; }
    int getEventType() { return eventType; }
    void setEventType(int type) { eventType = type; }
};



#endif //INPUT_H
