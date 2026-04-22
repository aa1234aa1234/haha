#shader vertex
#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 Pos;
layout(location = 2) in vec2 aSize;
layout(location = 3) in int isSelected;
out vec2 pos;
out int selected;

uniform mat4 projection;

void main() {
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0,0.0,0.0,1.0);
}