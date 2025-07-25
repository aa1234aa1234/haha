#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormalCoord;
layout(location = 2) in vec2 aTexCoord;
out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    vertexColor = vec4(0.5,0.0,0.0,1.0);
    Normal = aNormalCoord;
}