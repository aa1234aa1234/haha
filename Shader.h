#pragma once
#include "header.h"
#include <fstream>
#include <string>
class Shader
{
	unsigned int id;
public:
	Shader(const char* filepath1, const char* filepath2);
	Shader();
	~Shader();
	void createFromSource(const std::string& vertexsrc, const std::string& fragsrc);
	void use();
	unsigned int getId();
};

