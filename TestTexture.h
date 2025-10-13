#pragma once
#include <iostream>

class TestTexture
{
	unsigned int id;
	std::string type;
	std::string path;
public:
	TestTexture(unsigned int id, std::string& type, std::string& filepath);
	TestTexture(const char* type);
	TestTexture();
	~TestTexture();
	unsigned int getId();
	std::string getType();
	std::string getPath();
	void setId(unsigned int id1);
	void setPath(std::string path);
	void setType(std::string type);
};

