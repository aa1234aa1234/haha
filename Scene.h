#pragma once
#include "Camera.h"
#include "Object.h"
#include "FrameBuffer.h"
#include "Shader.h"
class Scene
{
	Camera* camera = new Camera();
	FrameBuffer sceneBuffer;
	Shader *sceneShader, *planeShader;
	std::vector<Object> objects;
public:
	Scene(int& w, int& h);
	~Scene();
	void renderScene();
	void addObject(Object& object);
	Camera* getCamera();
	unsigned int getSceneTexture();
	void resizeSceneBuffer(int& width, int& height);
};

