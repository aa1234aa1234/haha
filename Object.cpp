#include "Object.h"

Object::Object(const Model& model) {
	this->model = model;
}

Object::~Object() {

}

glm::mat4 Object::getModelMatrix() {
	modelMatrix = glm::translate(glm::mat4(1.0f), model.position);
	modelMatrix = glm::scale(modelMatrix, model.scale);
	return modelMatrix;
}

void Object::Draw(Shader& shader) {
	model.Draw(shader);
}

void Object::Unbind() {
	model.Unbind();
}

Model& Object::getModel() {
	return model;
}