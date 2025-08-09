#pragma once
#include "header.h"
#include <stb/stb_image.h>
#include "FrameBuffer.h"
#include "Shader.h"
#include <map>

typedef struct Character {
	int x, y, width, height, originX, originY, advance;
};

typedef struct Text {
    float posx, posy;
    std::string text;
	float textScale = 0.5f;
	unsigned int frameBuffer;
};

class TextHandler {
	static TextHandler* instance;
	FrameBuffer* textBuffer;
	int width, height, textureWidth, textureHeight;
	unsigned int textureId;
	std::map<char, Character> characters;
    std::vector<Text> text;
    Shader* shader;
    float textScale = 0.5f;
    unsigned int vao, vbo;
public:
	TextHandler(int w, int h, const char* filepath) : width(std::move(w)), height(std::move(h)) {
		textBuffer = new FrameBuffer();
        shader = new Shader("resources/shader/vertex3.glsl", "resources/shader/frag3.glsl");
		textBuffer->init(width, height);
		ImportAtlas(filepath);
        shader->use();
        glUniform1f(glGetUniformLocation(shader->getId(), "width"), static_cast<float>(width));
        glUniform1f(glGetUniformLocation(shader->getId(), "height"), static_cast<float>(height));
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float)*2));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	~TextHandler() {
		delete textBuffer;
		/*for (auto& p : text) {
			delete p;
		}
		text.clear();*/
        delete shader;
		glDeleteTextures(1, &textureId);
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
	}

	static TextHandler* getInstance()
	{
		return instance;
	}

	static void makeInstance(int w, int h, const char* filepath)
	{
		if (instance == 0) instance = new TextHandler(w, h, filepath);
	}

	static void destroyInstance()
	{
		delete instance;
		instance = nullptr;
	}

    unsigned int getFrameTexture() {
        return textBuffer->getFrameTexture();
    }

    int addText(float posx, float posy, std::string text, float textscale = 0.5f, unsigned int frameBuffer = 0) {
        this->text.push_back({ posx,posy,text, textscale, frameBuffer });
        return this->text.size()-1;
    }

    void editText(float posx, float posy, std::string text, int idx, float textscale = 0.5f, unsigned int frameBuffer = 0) {
        this->text[idx] = { posx, posy, text, textscale, frameBuffer };
    }

	int removeText(int idx)
	{
		this->text.erase(this->text.begin() + idx);
		return -1;
	}

	void draw() {
        shader->use();
        //textBuffer->bind();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindVertexArray(vao);
        for (auto& k : text) {
            float x = k.posx;
            float y = k.posy;
            float mx = 1e9;
        	if (k.frameBuffer)
        	{
        		std::cout << "fewafwae " << k.frameBuffer << std::endl;
        		glBindFramebuffer(GL_FRAMEBUFFER, k.frameBuffer);
        	}
            for (auto& p : k.text) {
                if (characters[p].height < mx) mx = characters[p].height;
            }
            for (auto& p : k.text) {

                Character ch = characters[p];
                //float xpos = (k.posx - ch.originX * k.textScale) / (width / 2.0) - 1, xpos1 = (k.posx - ch.originX * k.textScale + ch.width * k.textScale) / (width / 2.0) - 1;
                //float ypos = 1.0 - (k.posy - (ch.originY) * k.textScale) / (height / 2.0), ypos1 = 1.0 - ((k.posy - ch.originY * k.textScale) + ch.height * k.textScale) / (height / 2.0);
                //float ypos = 1.0 - (posy - ch.originY * k.textScale) / (height / 2.0), ypos1 = 1.0 - ((posy - ch.originY * k.textScale + ch.height * k.textScale)) / (height / 2.0);

                float w = ch.width * k.textScale;
                float h = ch.height * k.textScale;
                float xpos = k.posx - ch.originX * k.textScale, xpos1 = xpos+w;
                float ypos = k.posy+mx*k.textScale - ch.originY * k.textScale, ypos1 = ypos+h;
                float x = ch.x / (float)textureWidth, y = ch.y / (float)textureHeight;
                float x1 = (ch.x + ch.width) / (float)textureWidth, y1 = (ch.y + ch.height) / (float)textureHeight;
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                float vertices[6][4] = {
                    xpos, ypos, x, y,
                    xpos1, ypos, x1, y,
                    xpos1, ypos1, x1, y1,
                    xpos, ypos, x, y,
                    xpos1, ypos1, x1, y1,
                    xpos, ypos1, x, y1
                };
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * 4, vertices);
                //std::vector<float> aa(24);
                //glGetBufferSubData(GL_ARRAY_BUFFER, 0, 6 * 4 * sizeof(float), aa.data());
                glDrawArrays(GL_TRIANGLES, 0, 6);
                k.posx += ch.advance * k.textScale;
            }
            k.posx = x;
            k.posy = y;
        }
        //textBuffer->unbind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

	void ImportAtlas(const char* path) {
		glGenTextures(1, &textureId);
		int components;
		unsigned char* data = stbi_load(path, &textureWidth, &textureHeight, &components, 0);
		if (data) {
			GLenum format;
			switch (components) {
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			}
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_image_free(data);
			//glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			std::cout << "texture failed to load " << path << std::endl;
			stbi_image_free(data);
		}
        
        /*characters = {
    { '0', {95, 43, 18, 20, 6, 14, 6} },
    { '1', {103, 63, 16, 20, 5, 14, 6} },
    { '2', {113, 43, 18, 20, 6, 14, 6} },
    { '3', {131, 43, 18, 20, 6, 14, 6} },
    { '4', {149, 43, 18, 20, 6, 14, 6} },
    { '5', {167, 43, 18, 20, 6, 14, 6} },
    { '6', {185, 43, 18, 20, 6, 14, 6} },
    { '7', {203, 43, 18, 20, 6, 14, 6} },
    { '8', {221, 43, 18, 20, 6, 14, 6} },
    { '9', {239, 43, 18, 20, 6, 14, 6} },
    { ' ', {82, 101, 12, 12, 6, 6, 3} },
    { '!', {166, 63, 14, 20, 5, 14, 3} },
    { '"', {261, 83, 16, 15, 6, 14, 4} },
    { '#', {202, 23, 19, 20, 6, 14, 6} },
    { '$', {144, 0, 18, 22, 6, 15, 6} },
    { '%', {278, 0, 22, 20, 5, 14, 10} },
    { '&', {42, 23, 20, 20, 6, 14, 8} },
    { '\'', {293, 83, 14, 15, 6, 14, 2} },
    { '(', {55, 0, 15, 23, 5, 14, 4} },
    { ')', {70, 0, 15, 23, 5, 14, 4} },
    { '*', {277, 83, 16, 15, 6, 14, 4} },
    { '+', {276, 63, 18, 18, 5, 13, 7} },
    { ',', {307, 83, 14, 14, 5, 7, 3} },
    { '-', {38, 101, 16, 13, 6, 9, 4} },
    { '.', {54, 101, 14, 13, 5, 7, 3} },
    { '/', {87, 63, 16, 20, 6, 14, 3} },
    { ':', {212, 83, 14, 18, 5, 12, 3} },
    { ';', {220, 63, 14, 19, 5, 12, 3} },
    { '<', {294, 63, 18, 18, 5, 13, 7} },
    { '=', {243, 83, 18, 15, 5, 12, 7} },
    { '>', {0, 83, 18, 18, 5, 13, 7} },
    { '?', {257, 43, 18, 20, 6, 14, 6} },
    { '@', {0, 0, 23, 23, 5, 14, 12} },
    { 'A', {300, 0, 21, 20, 6, 14, 8} },
    { 'B', {221, 23, 19, 20, 5, 14, 8} },
    { 'C', {62, 23, 20, 20, 6, 14, 8} },
    { 'D', {82, 23, 20, 20, 5, 14, 8} },
    { 'E', {240, 23, 19, 20, 5, 14, 8} },
    { 'F', {275, 43, 18, 20, 5, 14, 7} },
    { 'G', {102, 23, 20, 20, 5, 14, 9} },
    { 'H', {259, 23, 19, 20, 5, 14, 8} },
    { 'I', {180, 63, 14, 20, 5, 14, 3} },
    { 'J', {36, 63, 17, 20, 6, 14, 6} },
    { 'K', {278, 23, 19, 20, 5, 14, 8} },
    { 'L', {293, 43, 18, 20, 5, 14, 6} },
    { 'M', {0, 23, 21, 20, 5, 14, 10} },
    { 'N', {297, 23, 19, 20, 5, 14, 8} },
    { 'O', {21, 23, 21, 20, 6, 14, 9} },
    { 'P', {0, 43, 19, 20, 5, 14, 8} },
    { 'Q', {162, 0, 21, 21, 6, 14, 9} },
    { 'R', {122, 23, 20, 20, 5, 14, 8} },
    { 'S', {19, 43, 19, 20, 6, 14, 8} },
    { 'T', {38, 43, 19, 20, 6, 14, 7} },
    { 'U', {57, 43, 19, 20, 5, 14, 8} },
    { 'V', {142, 23, 20, 20, 6, 14, 8} },
    { 'W', {255, 0, 23, 20, 6, 14, 11} },
    { 'X', {162, 23, 20, 20, 6, 14, 8} },
    { 'Y', {182, 23, 20, 20, 6, 14, 8} },
    { 'Z', {76, 43, 19, 20, 6, 14, 7} },
    { '[', {85, 0, 15, 23, 5, 14, 3} },
    { '\\', {119, 63, 16, 20, 6, 14, 3} },
    { ']', {100, 0, 15, 23, 6, 14, 3} },
    { '^', {226, 83, 17, 16, 6, 14, 5} },
    { '_', {0, 101, 19, 13, 6, 4, 6} },
    { '`', {68, 101, 14, 13, 5, 14, 4} },
    { 'a', {18, 83, 18, 18, 6, 12, 6} },
    { 'b', {0, 63, 18, 20, 5, 14, 6} },
    { 'c', {36, 83, 18, 18, 6, 12, 6} },
    { 'd', {18, 63, 18, 20, 6, 14, 6} },
    { 'e', {54, 83, 18, 18, 6, 12, 6} },
    { 'f', {135, 63, 16, 20, 6, 14, 3} },
    { 'g', {183, 0, 18, 21, 6, 12, 6} },
    { 'h', {53, 63, 17, 20, 5, 14, 6} },
    { 'i', {194, 63, 13, 20, 5, 14, 2} },
    { 'j', {115, 0, 15, 23, 7, 14, 2} },
    { 'k', {70, 63, 17, 20, 5, 14, 6} },
    { 'l', {207, 63, 13, 20, 5, 14, 2} },
    { 'm', {234, 63, 21, 18, 5, 12, 10} },
    { 'n', {162, 83, 17, 18, 5, 12, 6} },
    { 'o', {72, 83, 18, 18, 6, 12, 6} },
    { 'p', {201, 0, 18, 21, 5, 12, 6} },
    { 'q', {219, 0, 18, 21, 6, 12, 6} },
    { 'r', {196, 83, 16, 18, 5, 12, 4} },
    { 's', {90, 83, 18, 18, 6, 12, 6} },
    { 't', {151, 63, 15, 20, 6, 14, 3} },
    { 'u', {179, 83, 17, 18, 5, 12, 6} },
    { 'v', {108, 83, 18, 18, 6, 12, 6} },
    { 'w', {255, 63, 21, 18, 6, 12, 8} },
    { 'x', {126, 83, 18, 18, 6, 12, 6} },
    { 'y', {237, 0, 18, 21, 6, 12, 6} },
    { 'z', {144, 83, 18, 18, 6, 12, 6} },
    { '{', {23, 0, 16, 23, 6, 14, 4} },
    { '|', {130, 0, 14, 23, 5, 14, 3} },
    { '}', {39, 0, 16, 23, 6, 14, 4} },
    { '~', {19, 101, 19, 13, 6, 11, 7} }
        };*/
        characters = {
            { '0', {258,77,27,35,5,29,18} },
    { '1', {73,112,21,35,3,29,18} },
    { '2', {90,77,28,35,5,29,18} },
    { '3', {285,77,27,35,5,29,18} },
    { '4', {118,77,28,35,6,29,18} },
    { '5', {146,77,28,35,5,28,18} },
    { '6', {312,77,27,35,5,29,18} },
    { '7', {178,112,27,34,5,28,18} },
    { '8', {174,77,28,35,5,29,18} },
    { '9', {202,77,28,35,5,29,18} },
    { ' ', {392,147,12,12,6,6,9} },
    { '!', {115,112,16,35,3,29,9} },
    { '"', {225,147,21,20,5,29,11} },
    { '#', {393,0,30,36,6,29,18} },
    { '$', {197,0,27,40,5,30,18} },
    { '%', {42,42,37,35,4,29,28} },
    { '&', {361,0,32,36,5,29,21} },
    { '\'', {246,147,16,20,5,29,6} },
    { '(', {85,0,20,42,4,29,10} },
    { ')', {105,0,20,42,4,29,10} },
    { '*', {202,147,23,22,5,29,12} },
    { '+', {64,147,28,27,4,24,18} },
    { ',', {262,147,16,19,3,9,9} },
    { '-', {324,147,21,15,5,15,10} },
    { '.', {345,147,16,15,3,9,9} },
    { '/', {478,0,21,36,6,29,9} },
    { ':', {48,147,16,28,3,22,9} },
    { ';', {205,112,16,33,3,22,9} },
    { '<', {92,147,28,27,4,25,18} },
    { '=', {174,147,28,22,4,22,18} },
    { '>', {120,147,28,27,4,25,18} },
    { '?', {339,77,27,35,5,29,18} },
    { '@', {0,0,42,42,4,29,32} },
    { 'A', {79,42,34,35,6,29,21} },
    { 'B', {497,42,30,35,4,29,21} },
    { 'C', {328,0,33,36,5,29,23} },
    { 'D', {279,42,32,35,4,29,23} },
    { 'E', {0,77,30,35,4,29,21} },
    { 'F', {230,77,28,35,4,29,19} },
    { 'G', {294,0,34,36,4,29,25} },
    { 'H', {311,42,31,35,4,29,23} },
    { 'I', {131,112,16,35,3,29,9} },
    { 'J', {26,112,25,35,5,29,16} },
    { 'K', {342,42,31,35,4,29,21} },
    { 'L', {366,77,27,35,4,29,18} },
    { 'M', {113,42,34,35,4,29,26} },
    { 'N', {373,42,31,35,4,29,23} },
    { 'O', {259,0,35,36,5,29,25} },
    { 'P', {30,77,30,35,4,29,21} },
    { 'Q', {224,0,35,37,5,29,25} },
    { 'R', {147,42,33,35,4,29,23} },
    { 'S', {404,42,31,35,5,29,21} },
    { 'T', {435,42,31,35,5,29,19} },
    { 'U', {466,42,31,35,4,29,23} },
    { 'V', {180,42,33,35,6,29,21} },
    { 'W', {0,42,42,35,6,29,30} },
    { 'X', {213,42,33,35,6,29,21} },
    { 'Y', {246,42,33,35,6,29,21} },
    { 'Z', {60,77,30,35,5,29,19} },
    { '[', {159,0,19,41,4,29,9} },
    { '\\', {499,0,21,36,6,29,9} },
    { ']', {178,0,19,41,6,29,9} },
    { '^', {148,147,26,24,5,29,15} },
    { '_', {361,147,31,14,7,1,18} },
    { '`', {306,147,18,16,5,29,10} },
    { 'a', {403,112,27,29,5,23,18} },
    { 'b', {393,77,27,35,4,29,18} },
    { 'c', {430,112,27,29,5,23,16} },
    { 'd', {420,77,27,35,5,29,18} },
    { 'e', {291,112,28,29,5,23,18} },
    { 'f', {51,112,22,35,6,29,9} },
    { 'g', {451,0,27,36,5,23,18} },
    { 'h', {501,77,26,35,4,29,18} },
    { 'i', {147,112,16,35,4,29,7} },
    { 'j', {125,0,19,42,8,29,7} },
    { 'k', {0,112,26,35,4,29,16} },
    { 'l', {163,112,15,35,4,29,7} },
    { 'm', {221,112,35,29,4,23,26} },
    { 'n', {484,112,26,29,4,23,18} },
    { 'o', {319,112,28,29,5,23,18} },
    { 'p', {447,77,27,35,4,23,18} },
    { 'q', {474,77,27,35,5,23,18} },
    { 'r', {26,147,22,29,4,23,10} },
    { 's', {510,112,26,29,5,23,16} },
    { 't', {94,112,21,35,6,29,9} },
    { 'u', {0,147,26,29,4,23,18} },
    { 'v', {347,112,28,29,6,23,16} },
    { 'w', {256,112,35,29,6,23,23} },
    { 'x', {375,112,28,29,6,23,16} },
    { 'y', {423,0,28,36,6,23,16} },
    { 'z', {457,112,27,29,6,23,16} },
    { '{', {42,0,22,42,5,29,10} },
    { '|', {144,0,15,42,3,29,8} },
    { '}', {64,0,21,42,5,29,10} },
    { '~', {278,147,28,17,5,20,18} }
        };
	}
};