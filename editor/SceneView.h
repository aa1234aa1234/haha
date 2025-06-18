#pragma once
#include "../header.h"
#include "UIComponent.h"
#include "../Scene.h"
#include <map>

class SceneView : public UIComponent {

	

	std::vector<Scene*> scenes;
	std::vector<unsigned int> sceneTextures;
	std::map<std::string, unsigned int> textures;
	std::vector<UIElements> sceneviewtabs;
	int selectedscene = 0;
public:
	SceneView() : UIComponent() {
		genVertices();
	}

	~SceneView() {
		for (auto& p : scenes) {
			delete p;
		}
		scenes.clear();
	}

	void addScene(Scene* scene) {
		scenes.reserve(scenes.size() + 1);
		scenes.emplace_back(scene);
	}

	void addSceneTexture(const std::string& scenename, const unsigned int& texture)
	{
		sceneTextures.emplace_back(texture);
		textures[scenename] = texture;
	}

	unsigned int getSceneTexture() {
		return sceneTextures.size() ? sceneTextures[selectedscene] : scenes[selectedscene]->getSceneTexture();
	}

	void renderScene() {
		//scenes[selectedscene]->renderScene();
		glBindTexture(GL_TEXTURE_2D, getSceneTexture());
	}

	virtual void genVertices() override {
		
		//generateQuad();
		for (int i = 0; i < 2; i++) {
			sceneviewtabs.push_back({ glm::vec2(1.0,1.0),glm::vec2(1.0,1.0),glm::vec3(0.225,0.225,0.225) });
			sceneviewtabs.push_back({ glm::vec2(1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec3(0.225,0.225,0.225) });
			sceneviewtabs.push_back({ glm::vec2(-1.0,1.0),glm::vec2(-1.0,1.0),glm::vec3(0.225,0.225,0.225) });
			sceneviewtabs.push_back({ glm::vec2(-1.0,-1.0),glm::vec2(-1.0,-1.0),glm::vec3(0.225,0.225,0.225) });
			sceneviewtabs.push_back({ glm::vec2(1.0,-1.0),glm::vec2(1.0,-1.0),glm::vec3(0.225,0.225,0.225) });
			sceneviewtabs.push_back({ glm::vec2(-1.0,1.0),glm::vec2(-1.0,1.0),glm::vec3(0.225,0.225,0.225) });
		}
	}

	/*virtual void DrawComponent(Shader* shader) override {
		glm::mat4 matrix = glm::mat4(1.0);
		matrix = glm::translate(matrix, glm::vec3(position.x, position.y+25.0, 0.0));
		matrix = glm::scale(matrix, glm::vec3(size.x, size.y-25.0, 0.0));
		
		glBindTexture(GL_TEXTURE_2D, scenes[selectedscene]->getSceneTexture());
		glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));
		glUniform1i(glGetUniformLocation(shader->getId(), "a"), 1);
		
		glDrawArrays(GL_TRIANGLES, 0, uielements.size());
		glBindTexture(GL_TEXTURE_2D, 0);
		glUniform1i(glGetUniformLocation(shader->getId(), "a"), 0);
		matrix = glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, 0.0));
		matrix = glm::scale(matrix, glm::vec3(size.x, 25.0, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(UIElements) * sceneviewtabs.size(), sceneviewtabs.data());
		glDrawArrays(GL_TRIANGLES, 0, sceneviewtabs.size());
		for (auto& p : sceneviewtabs) {
			

		}
	}*/

	int onClick(glm::vec2 pos) override {
		return getComponentId();
	}

	int onDrag(glm::vec2 pos, glm::vec2 pos2) override {
		pos = glm::vec2(pos.x - pos2.x, pos2.y - pos.y);
		float sensitivity = 0.2f;
		pos.x = (pos.x * sensitivity);
		pos.y = (pos.y * sensitivity);
		scenes[selectedscene]->getCamera()->yaw += pos.x;
		scenes[selectedscene]->getCamera()->pitch += pos.y;
		if (scenes[selectedscene]->getCamera()->pitch > 89.0f) scenes[selectedscene]->getCamera()->pitch = 89.0f;
		if (scenes[selectedscene]->getCamera()->pitch < -89.0f) scenes[selectedscene]->getCamera()->pitch = -89.0f;
		//std::cout << scenes[selectedscene]->getCamera()->yaw << ' ' << scenes[selectedscene]->getCamera()->pitch << std::endl;
		glm::vec3 direction, direction2;
		direction.x = cos(glm::radians(scenes[selectedscene]->getCamera()->yaw)) * cos(glm::radians(scenes[selectedscene]->getCamera()->pitch));
		direction.y = sin(glm::radians(scenes[selectedscene]->getCamera()->pitch));
		direction.z = sin(glm::radians(scenes[selectedscene]->getCamera()->yaw)) * cos(glm::radians(scenes[selectedscene]->getCamera()->pitch));
		direction = glm::normalize(direction);
		direction2.x = cos(glm::radians(scenes[selectedscene]->getCamera()->yaw)) * cos(glm::radians(0.0f));
		direction2.y = sin(glm::radians(0.0f));
		direction2.z = sin(glm::radians(scenes[selectedscene]->getCamera()->yaw)) * cos(glm::radians(0.0f));
		direction2 = glm::normalize(direction2);
		scenes[selectedscene]->getCamera()->camerafront = direction;
		scenes[selectedscene]->getCamera()->cameradirection = direction2;
		return -1;
	}
};