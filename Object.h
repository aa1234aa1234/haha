#pragma once
#include "header.h"
#include "Model.h"
#include "Shader.h"
class Object
{
	Model model=Model();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
public:
	Object(const Model& model);
	~Object();
	glm::mat4 getModelMatrix();
	void Draw(Shader& shader);
	void Unbind();
	Model& getModel();
};

