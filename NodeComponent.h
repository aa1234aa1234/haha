//
// Created by sw_303 on 2025-06-21.
//

#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H

class Shader;
class Camera;
class SceneNode;

class NodeComponent {
    SceneNode* parent;
public:
    NodeComponent() : parent(nullptr) {}
    virtual ~NodeComponent() {}

    void setParent(SceneNode* node) { this->parent = node; }
    //for render components
    virtual void render(Shader* shader, Camera* camera) {}
    //for scripts
    virtual void update(float deltatime) {}
    virtual void handleInput() {}
};



#endif //NODECOMPONENT_H
