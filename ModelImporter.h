#pragma once
#include "header.h"
#include <string>

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include "TestMesh.h"
#include "Model.h"



struct Material {
	std::string name;
	glm::vec3 ambiant;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	TestTexture texture;
	Material() : ambiant(glm::vec3(0.0f, 0.0f, 0.0f)), diffuse(glm::vec3(0.0f, 0.0f, 0.0f)), specular(glm::vec3(0.0f, 0.0f, 0.0f)), name("") {

	}
};



class ModelImporter {
public:
	
	ModelImporter() {
		
	}

	Model loadModel(const char* filepath) {
		std::ifstream stream(filepath, std::ios::in);
		std::string line;
		std::vector<glm::vec3> position;
		std::vector<glm::vec2> texcoord;
		std::vector<glm::vec3> normal;
		std::vector<unsigned int> indices;
		std::vector<TestMesh*> meshes;
		std::unordered_map<std::string, Material> mats;
		std::string str = std::string(filepath);
		std::string str1;
		str1 += std::strtok((char*)str.c_str(), "/");
		str1 += "/";
		str1 += std::strtok(NULL, "/");
		const char* directory = str1.c_str();
		std::string currentMesh;
		int linecnt = 0;
		while (std::getline(stream, line)) {
			std::istringstream iss(line);
			std::string a;
			iss >> a;
			if (a == "mtllib") {
				std::string file;
				iss >> file;
				loadMaterials(file.c_str(), directory, mats);
			}
			if (a == "g" || a == "o") {
				TestMesh* mesh = loadMesh(stream, position, texcoord, normal, mats);
				meshes.reserve(meshes.size() + 1);
				meshes.emplace_back(mesh);
			}
			if (a == "v") {
				glm::vec3 vec;
				iss >> vec.x >> vec.y >> vec.z;
				position.push_back(vec);
			}
			if (a == "vt") {
				glm::vec2 texvec;
				iss >> texvec.x >> texvec.y;
				texcoord.push_back(texvec);
			}
			if (a == "vn") {
				glm::vec3 nvec;
				iss >> nvec.x >> nvec.y >> nvec.z;
				normal.push_back(nvec);
			}
		}
		//std::cout << meshes[0].vertices.size() << std::endl;
		return Model(meshes);
	}

	TestMesh* loadMesh(std::ifstream& stream, std::vector<glm::vec3>& position, std::vector<glm::vec2>& texcoord, std::vector<glm::vec3>& normal, std::unordered_map<std::string,Material>& mats) {
		std::streampos aaaaaaaaaaaaaaaaaaaa = stream.tellg();
		std::string line;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<TestTexture> textures;
		while (std::getline(stream, line)) {
			std::istringstream iss(line);
			std::string a;
			iss >> a;
			
			if (a == "usemtl") {
				std::string name;
				iss >> name;
				textures.push_back(mats[name].texture);
			}
			if (a == "f") {
				for (int i = 0; i < 3; i++) {
					Vertex vertex;
					int pos, tex=-1, normal1=-1;
					char slash;
					bool flag = false;
					iss >> pos >> slash >> tex >> slash >> normal1;
					
					vertex.Position = position[pos - 1];
					indices.push_back(indices.size());
					if (tex == -1) {
						vertex.Normal = normal[normal1 - 1];
						//indices.push_back(normal1 - 1);
					}
					else if (normal1 == -1) {
						vertex.TexCoords = texcoord[tex - 1];
						//indices.push_back(tex - 1);
					}
					else {
						vertex.TexCoords = texcoord[tex - 1];
						vertex.Normal = normal[normal1 - 1];
						//indices.push_back(normal1 - 1);
						//indices.push_back(tex - 1);
					}
					/*for (auto& p : vertices) {
						if (check(p,vertex)) flag = true;
					}*/
					//if(!flag) vertices.push_back(vertex);
					vertices.push_back(vertex);
				}
			}
			std::streampos pos = stream.tellg();
			std::getline(stream, line);
			iss = std::istringstream(line);
			iss >> a;
			if (a == "g" || a == "o") {  break; }
			else stream.seekg(pos);
		}
		stream.seekg(aaaaaaaaaaaaaaaaaaaa);
		return new TestMesh(vertices,indices,textures);
	}
	
	void loadMaterials(const char* filename, const char* directory, std::unordered_map<std::string,Material> &mats) {
		std::ifstream stream(std::string(directory) + '/' + std::string(filename).c_str(), std::ios::in);
		std::string line;
		std::map<std::string, std::string> texturetype;
		texturetype["map_Kd"] = "diffuse";
		texturetype["map_Ks"] = "specular";
		Material currentmat;
		while(std::getline(stream, line)) {
			std::istringstream iss(line);
			std::string a;
			iss >> a;
			if (a == "newmtl") {
				std::string name;
				iss >> name;
				if (currentmat.name.size() != 0 && currentmat.name != name) {
					
					mats[currentmat.name] = currentmat;
				}
				//currentmat = Material();
				currentmat.name = name;
			}
			else if (a == "Ka") {
				iss >> currentmat.ambiant.x >> currentmat.ambiant.y >> currentmat.ambiant.z;
			}
			else if (a == "Kd") {
				iss >> currentmat.diffuse.x >> currentmat.diffuse.y >> currentmat.diffuse.z;
			}
			else if (a == "Ks") {
				iss >> currentmat.specular.x >> currentmat.specular.y >> currentmat.specular.z;
			}
			else if (a == "Ns") {
				iss >> currentmat.shininess;
			}
			else if (a == "map_Kd" || a == "map_Ks") {
				std::string file;
				iss >> file;
				file = file.replace(0, 1, directory);
				file = file.replace(strlen(directory), 1, "/");
				currentmat.texture.setPath(file);
				currentmat.texture.setType(texturetype[a]);
				currentmat.texture.setId(getTextureFromFile(file.c_str()));
				std::cout << file << ": " << currentmat.texture.getId() << std::endl;
			}
		}
		mats[currentmat.name] = currentmat;
	}

	unsigned int getTextureFromFile(const char* filepath, bool gamma = false);

	void print();

	bool check(Vertex& v, Vertex& v2);
};