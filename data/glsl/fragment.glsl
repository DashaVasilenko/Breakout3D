#version 430 core

in struct FragmentData {
    vec2 uv;
} fragmentData;

out vec4 outColor;

void main() {
    outColor = vec4(fragmentData.uv, 0.0, 1.0);
    //outColor = vec4(1.0f, 0.0f, 0.0, 1.0);
} 