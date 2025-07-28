//
// Created by user on 7/21/2025.
//

#ifndef EXPANDICON_H
class ExpandIcon
{
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0,
    };
    unsigned int vao,vbo;
    Shader* shader = nullptr;
    const char* vertex = R"(
    #version 330 core

    layout(location = 0) in vec2 position;

    out vec2 pos;

    uniform mat4 projection;

    void main() {
        pos = position;
        if(pos.x == -1.0) pos.x = 0;
        if(pos.y == -1.0) pos.y = 0;
        gl_Position = projection * vec4(pos, 0.0, 1.0);

    }
    )";

    const char* frag = R"(
    #version 330 core

    layout (location = 0) out vec4 fragColor;

    in vec2 pos;

	vec4 NormalizeRGB(vec4 color) {
		return vec4(color.xyz/255.0,color.a);
	}

    void main() {
        fragColor = vec4(NormalizeRGB(vec4(100,100,100,1.0));
    }
    )";
public:
    glm::vec2 position;
    glm::vec2 size;
    bool visible = true, expanded = false;
    ExpandIcon(glm::vec2 pos, glm::vec2 size)
    {
        position = pos;
        this->size = size;
        shader = new Shader();
        shader->createFromSource(vertex,frag);

        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ndc, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shader->use();
        glm::mat4 mat = glm::ortho(0.0f, 1200.0f, 900.0f, 0.0f);
        mat = glm::translate(mat, glm::vec3(pos, 0.0f));
        mat = glm::scale(mat, glm::vec3(size, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
    }

    ExpandIcon() {}

    void render()
    {
        if (!visible) return;
        // shader->use();
        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    bool onClick(glm::vec2 pos) {
        if (!visible) return false;
        return position.x <= pos.x && pos.x <= position.x + size.x && position.y <= pos.y && pos.y <= position.y + size.y;
    }
};

#define EXPANDICON_H

#endif //EXPANDICON_H
