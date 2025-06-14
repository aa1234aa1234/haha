#pragma once
#include "header.h"
#include "Mesh.h"

class Model
{
	std::vector<Mesh*> meshes;
	
public:
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	Model(std::vector<Mesh*> meshes) : meshes(std::move(meshes)) {}
	Model();
	~Model();
	void Draw(Shader& shader);
	void setMesh(std::vector<Mesh*>& meshes);
	void Unbind();
};

