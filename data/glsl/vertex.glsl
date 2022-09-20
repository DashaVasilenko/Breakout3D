#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
out struct FragmentData {
    vec2 uv;
} fragmentData;

void main() { 
    fragmentData.uv = uv;
    //gl_Position = MVP*vec4(position, 1.0f);
    gl_Position = Projection*View*Model*vec4(position, 1.0f);
} 