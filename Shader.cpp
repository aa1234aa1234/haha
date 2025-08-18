#include "Shader.h"

Shader::Shader(const char* filepath1, const char* filepath2) {
	std::string content1 = "", content2 = "",line="";
	std::ifstream wah(filepath1, std::ios::in);
	std::ifstream wa(filepath2, std::ios::in);
	unsigned int vertexshader=glCreateShader(GL_VERTEX_SHADER), fragmentshader=glCreateShader(GL_FRAGMENT_SHADER);
	while (!wah.eof()) {
		std::getline(wah, line);
		content1.append(line + "\n");
	}
	line = "";
	while (!wa.eof()) {
		std::getline(wa, line);
		content2.append(line + "\n");
	}
	const char* a = content1.c_str();
	const char* aa = content2.c_str();
	glShaderSource(vertexshader, 1, &a, NULL);
	glCompileShader(vertexshader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &aa, NULL);
	glCompileShader(fragmentshader);
	
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	id = glCreateProgram();
	glAttachShader(id, vertexshader);
	glAttachShader(id, fragmentshader);
	glLinkProgram(id);
	
	std::cout << id << "\n";
}

Shader::Shader() {
	
}

Shader::~Shader() {
	std::cout << "fewafawefaw " << id << std::endl;
	glDeleteProgram(id);
}

void Shader::createFromSource(const std::string& vertexsrc, const std::string& fragsrc) {
	std::string content1 = vertexsrc, content2 = fragsrc;
	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER), fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* a = content1.c_str();
	const char* aa = content2.c_str();
	glShaderSource(vertexshader, 1, &a, NULL);
	glCompileShader(vertexshader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &aa, NULL);
	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	id = glCreateProgram();
	glAttachShader(id, vertexshader);
	glAttachShader(id, fragmentshader);
	glLinkProgram(id);

	std::cout << id << "\n";
}

void Shader::use() {
	glUseProgram(id);
	//std::cout << "use " << id << std::endl;
	
	/*GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL Error after glUseProgram(): " << err << " " << id << std::endl;
	}*/
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << err << ' ' << id << ' ' << this << std::endl;
	}
}

unsigned int Shader::getId() {
	return id;
}
