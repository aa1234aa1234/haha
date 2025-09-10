//
// Created by sw_306 on 2025-09-01.
//

#ifndef PROJECT_ICONTEXTURES_H
#define PROJECT_ICONTEXTURES_H
#define EXPANDED_ARROW glm::vec4(0,0,696,564)
#define EXPAND_ARROW glm::vec4(696,0,696,564)
#include "glm/glm.hpp"

inline glm::vec4 GetIcon(glm::vec4 uvrect, glm::vec2 atlasSize) {
    return glm::vec4(uvrect.x/atlasSize.x,uvrect.y/atlasSize.y,uvrect.z/atlasSize.x, uvrect.w/atlasSize.y);
}

#endif //PROJECT_ICONTEXTURES_H