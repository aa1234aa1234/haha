#pragma once
#include "header.h"
#include "TestMesh.h"

class Model
{
	std::vector<TestMesh*> meshes;
	
public:
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	Model(std::vector<TestMesh*> meshes) : meshes(std::move(meshes)) {}
	Model();
	~Model();
	void Draw(Shader& shader);
	void setMesh(std::vector<TestMesh*>& meshes);
	void Unbind();
};

