#pragma once
#include "header.h"
#include "TestTexture.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//Vertex() : Position(glm::vec3(0.0f, 0.0f, 0.0f)), Normal(glm::vec3(0.0f, 0.0f, 0.0f)), TexCoords(glm::vec2(0.0f, 0.0f)) {}
};

class TestMesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TestTexture> textures;
	

	TestMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TestTexture> textures);
	~TestMesh();
	void Draw(Shader& shader);
	void Unbind();
private:
	unsigned int vao, vbo, ebo;
	void setupMesh();
};

