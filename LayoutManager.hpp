#pragma once
#include "header.h"
#include <map>

class LayoutManager {
	enum Layout {
		LEFT,
		RIGHT,
		CENTER,
		TOP,
		BOTTOM
	};
	std::map<int, std::pair<glm::vec2,glm::vec2>> position;
	int padding = 10;
public:
	LayoutManager() {}
	~LayoutManager() {}

	inline void getLayoutVertices(int& layout, std::vector<glm::vec2>& vertices) {
		glm::vec2 pos = position[layout].first, size = position[layout].second;


	}
};