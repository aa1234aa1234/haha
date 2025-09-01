//
// Created by sw_306 on 2025-09-01.
//

#ifndef PROJECT_ICONTEXTURES_H
#define PROJECT_ICONTEXTURES_H
#define EXPAND_ARROW glm::vec4(0,0,969,564);
#include "glm/glm.hpp"

inline glm::vec4 GetIcon(glm::vec4 uvrect, glm::vec2 atlasSize) {
    return glm::vec4(uvrect.x,uvrect.y,uvrect.z/atlasSize.x, uvrect.w/atlasSize.y);
}

#endif //PROJECT_ICONTEXTURES_H