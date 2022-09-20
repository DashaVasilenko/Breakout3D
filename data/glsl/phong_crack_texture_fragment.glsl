#version 430 core

in struct FragmentData {
    vec3 position;
    vec3 normal;
    vec2 uv; 
} fragmentData;

out vec4 outColor;

struct DirLight {
    mat4 lightMatrix;
    vec3 direction;
    bool hasShadowMap;
    vec3 color;
    float intensity;
};

layout (std140, binding = 0) uniform DirLights {
    DirLight dirLights[32];
    int cntLights;
};

layout (binding = 0) uniform sampler2D ambientColor;
layout (binding = 1) uniform sampler2D diffuseColor;
layout (binding = 2) uniform sampler2D specularColor;
uniform float shininess;
uniform vec2 tiling;

uniform sampler2D shadowMaps[4];

float CalculateShadow(int i, int j) {
    vec4 fragPosLightSpace = dirLights[i].lightMatrix*vec4(fragmentData.position, 1.0f);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz/fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords*0.5f + 0.5f;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMaps[j], projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = 0.005;
    // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    //float shadow = currentDepth - bias < closestDepth  ? 1.0f : 0.5f;

    // Percentage-closer filtering
    float shadow = 0.0f;
    vec2 texelSize = 1.0f/textureSize(shadowMaps[j], 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMaps[j], projCoords.xy + vec2(x, y)*texelSize).r;
            shadow += currentDepth - bias < pcfDepth ? 1.0f : 0.5f;
        }
    }
    shadow /= 9.0f;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 1.0;

    return shadow;
}


vec3 PhongShading(vec3 point, vec3 normal, int i, int j) {
    //const vec3 lightColor = vec3(1.0f); 

    float shadow = 1.0f;

    if (j < 4)
        shadow = dirLights[i].hasShadowMap ? CalculateShadow(i, j) : 1.0f;


    vec3 lightDirection = -normalize(dirLights[i].direction); // L
    vec3 inEye = normalize(-point); // V
    vec3 outNormal = normalize(normal); // N
    vec3 reflectedLight = reflect(-lightDirection, outNormal); //R

    //vec3 ambient = vec3(0.0f);
    //vec3 diffuse = vec3(0.0f);
    //vec3 specular = vec3(0.0f);
    //vec3 ambient = 0.1f*lightColor*texture(ambientColor, fragmentData.uv*tiling).rgb;
    vec3 diffuse = 0.8f*dirLights[i].color*texture(diffuseColor, fragmentData.uv*tiling).rgb*max(dot(lightDirection, outNormal), 0.0f);
    vec3 specular = 0.3f*dirLights[i].color*texture(specularColor, fragmentData.uv*tiling).rgb*pow(max(dot(inEye, reflectedLight), 0.0f), shininess);

    vec3 color = diffuse + specular;
    return color*dirLights[i].intensity*shadow;
}

void main() { 
    vec3 lightDir = vec3(0.0f, 1.0f, 0.0f);
    if (length(texture(diffuseColor, fragmentData.uv).rgb) < 0.7f)
        discard;
    else {
        vec3 color = 0.1f*texture(ambientColor, fragmentData.uv).rgb;
        int j = 0;
        for (int i = 0; i < cntLights; i++) {
            color += PhongShading(fragmentData.position, fragmentData.normal, i, j);
            if (dirLights[i].hasShadowMap)
                j++;
        }

        // luma based Reinhard tone mapping
        //vec3 exposure = vec3(0.126f, 0.7152f, 0.0722f);
        vec3 exposure = vec3(0.126f, 0.3152f, 0.0322f);
	    float luma = dot(color, exposure);
	    float toneMappedLuma = luma/(1.0 + luma);
	    color *= toneMappedLuma/luma;

        outColor = vec4(color, 1.0f);
    }

    //outColor = vec4(fragmentData.uv, 0.0, 1.0);
    //outColor = vec4(1.0f, 0.0f, 0.0, 1.0);
} 