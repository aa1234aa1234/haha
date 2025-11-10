#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;


uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * vec4(position,1.0);
}

#shader fragment
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess; //specular factor
};

struct BaseLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

out vec4 FragColor;

uniform Material material;
uniform BaseLight light;

void main() {
    FragColor = vec4(1.0,1.0,1.0,1.0);
}