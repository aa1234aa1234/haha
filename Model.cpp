#include "Model.h"

Model::Model() {

}

Model::~Model() {
	
}

std::ostream& operator<<(std::ostream& stream, Vertex& v) {
	stream << v.Position.x << ' ' << v.Position.y << ' ' << v.Position.z << ' ' << v.Position.x << ' ' << v.Normal.y << ' ' << v.Normal.z << ' ' << v.TexCoords.x << ' ' << v.TexCoords.y << std::endl;
	return stream;
}

void Model::Draw(Shader& shader) {
	for (auto& p : meshes) {
		p->Draw(shader);
	}
}

void Model::setMesh(std::vector<Mesh*>& meshes) {
	this->meshes = meshes;
}

void Model::Unbind() {
	for (auto& p : meshes) {
		p->Unbind();
	}
	for (auto& p : meshes) {
		delete p;
	}
	meshes.clear();
}