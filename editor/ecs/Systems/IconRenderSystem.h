//
// Created by sw_306 on 2025-09-01.
//

#ifndef PROJECT_ICONRENDERSYSTEM_H
#define PROJECT_ICONRENDERSYSTEM_H

class IconRenderSystem : public System {
    int width, height;
public:
    IconRenderSystem() {};
    ~IconRenderSystem() {};

    void Initialize(int& width, int& height) {
        this->width = width; this->height = height;
    }

    void Update() {

    }
};

#endif //PROJECT_ICONRENDERSYSTEM_H