#pragma once
#include "header.h"
#include "Texture.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//Vertex() : Position(glm::vec3(0.0f, 0.0f, 0.0f)), Normal(glm::vec3(0.0f, 0.0f, 0.0f)), TexCoords(glm::vec2(0.0f, 0.0f)) {}
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader& shader);
	void Unbind();
private:
	unsigned int vao, vbo, ebo;
	void setupMesh();
};

