#shader vertex
#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 Pos;
layout(location = 2) in vec2 aSize;
layout(location = 3) in int isSelected;
out vec2 pos;
out vec2 size;
out int selected;

uniform mat4 projection;

void main() {
    vec2 few = aPos;
    if(few.x == -1.0) few.x = 0.0;
    if(few.y == -1.0) few.y = 0.0;
    vec2 pos1 = aPos + (few*aSize);
    gl_Position = projection * vec4(pos1,1.0,1.0);
    pos = pos1;
    size = aSize;
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0,0.0,0.0,1.0);
}