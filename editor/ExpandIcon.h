//
// Created by user on 7/21/2025.
//

#ifndef EXPANDICON_H

class ExpandIcon
{
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0,
    };
public:
    glm::vec2 position;
    glm::vec2 size;
    bool visible = true, expanded = false;
    ExpandIcon(glm::vec2 pos, glm::vec2 size)
    {
        position = pos;
        this->size = size;
    }

    ExpandIcon() {}

    void render()
    {

    }

    bool onClick(glm::vec2 pos) {
        if (!visible) return false;
        return position.x <= pos.x && pos.x <= position.x + size.x && position.y <= pos.y && pos.y <= position.y + size.y;
    }
};

#define EXPANDICON_H

#endif //EXPANDICON_H
