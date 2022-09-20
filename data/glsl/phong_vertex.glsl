#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
out struct FragmentData {
    vec3 position;
    vec3 normal;
    vec2 uv;
} fragmentData;

void main() { 
    vec4 pos = Model*vec4(position, 1.0f);
    vec4 norm = transpose(inverse(Model))*vec4(normal, 0.0f);
    fragmentData.position = pos.xyz;
    fragmentData.normal = norm.xyz;
    fragmentData.uv = uv;
    //gl_Position = MVP*vec4(position, 1.0f);
    gl_Position = Projection*View*pos;

/*
    vec4 pos = View*Model*vec4(position, 1.0f);
    vec4 norm = View*Model*vec4(normal, 0.0f);
    fragmentData.position = pos.xyz;
    fragmentData.normal = norm.xyz;
    fragmentData.uv = uv;
    //gl_Position = MVP*vec4(position, 1.0f);
    gl_Position = Projection*pos;
*/
} 