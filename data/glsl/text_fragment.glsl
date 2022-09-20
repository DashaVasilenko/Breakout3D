#version 430 core

in vec2 texCoord;

out vec4 color;

layout (binding = 0) uniform sampler2D textTexture;
 

void main() {
    if (texture(textTexture, texCoord).r < 0.8f)
        discard;
    else
        color = vec4(vec3(texture(textTexture, texCoord).r), 1.0f);    

    //color = vec4(vec3(texture(textTexture, texCoord).r), 1.0f); 
        
    //color = vec4(vec3(texture(textTexture, texCoord).r), 1.0f);   
    //color = vec4(texCoord, 0.0f, 1.0f);
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}