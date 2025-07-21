//
// Created by D412 on 2025-07-21.
//

#ifndef ICON_H
#define ICON_H

class Icon
{
protected:
    unsigned int vao, vbo, texture;
    glm::vec2 position;
    glm::vec2 size;
public:
    Icon();
    virtual ~Icon();

    virtual bool onClick(glm::vec2 pos) = 0;
    virtual void render() = 0;
};

#endif //ICON_H