#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 texCoord;

uniform mat4 projection;

void main() {
    gl_Position = projection*vec4(position, 1.0f);
    texCoord = uv;
}