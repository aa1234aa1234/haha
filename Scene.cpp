#include "Scene.h"

Scene::Scene(int& w, int& h) {
	sceneBuffer.init(w, h);
	sceneShader = new Shader("resources/shader/vertexshader.glsl", "resources/shader/fragmentshader.glsl");
	//planeShader = new Shader("shader/planevertex.glsl", "shader/planefrag.glsl");
}

Scene::~Scene() {
	delete camera;
	delete sceneShader;
	delete planeShader;
	for (auto& p : objects) {
		p.Unbind();
	}
}

void Scene::renderScene() {
	
	camera->setCameraView();
	sceneBuffer.bind();
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneShader->use();
	glUniformMatrix4fv(glGetUniformLocation(sceneShader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(camera->projection));
	glUniformMatrix4fv(glGetUniformLocation(sceneShader->getId(), "view"), 1, GL_FALSE, glm::value_ptr(camera->view));
	for (auto& p : objects) {
		glUniformMatrix4fv(glGetUniformLocation(sceneShader->getId(), "model"), 1, GL_FALSE, glm::value_ptr(p.getModelMatrix()));
		p.Draw(*sceneShader);
	}
	sceneBuffer.unbind();
	glDisable(GL_DEPTH_TEST);
}

void Scene::addObject(Object& object) {
	objects.reserve(objects.size() + 1);
	objects.emplace_back(object);
	
}

Camera* Scene::getCamera() {
	return camera;
}

unsigned int Scene::getSceneTexture() {
	return sceneBuffer.getFrameTexture();
}

void Scene::resizeSceneBuffer(int& width, int& height) {
	sceneBuffer.resize(width, height);
}