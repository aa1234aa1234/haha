#include "TestTexture.h"
#include "header.h"

TestTexture::TestTexture(unsigned int id, std::string& type, std::string& filepath) {
	this->id = id;
	this->type = type;
	this->path = filepath;
}

TestTexture::TestTexture(const char* type) : type(type) {

}

TestTexture::TestTexture() {

}

TestTexture::~TestTexture() {
	//glDeleteTextures(1, &id);d
}

unsigned int TestTexture::getId() {
	return this->id;
}

std::string TestTexture::getType() {
	return this->type;
}

std::string TestTexture::getPath() {
	return this->path;
}

void TestTexture::setId(unsigned int id1) {
	this->id = id1;
}

void TestTexture::setPath(std::string path) {
	this->path = path;
}

void TestTexture::setType(std::string type) {
	this->type = type;
}
