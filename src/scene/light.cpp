#include "light.h"
#include "../core/errors.h"

namespace Bubble {

    void DirectionalLight::GenerateShadowMap(bool value) {
        if (!generateShadowMap && value) {
            GLCALL(glGenTextures(1, &shadowMap));
            GLCALL(glBindTexture(GL_TEXTURE_2D, shadowMap));
            GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
            GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
            GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        }

        generateShadowMap = value;
    }

    Mat4 DirectionalLight::GetLightMatrix() const {
        Mat4 lightProjection = Orthographic(-30.0f, 30.0f, -30.0f, 30.0f, 5.0f, 25.0f);
        Vec3 pos = transform.GetPosition();
        Mat4 lightView = LookAt(pos, pos + transform.GetForward(), Vec3(0.0, 1.0, 0.0));
        return lightProjection*lightView;
    }

    DirectionalLight::~DirectionalLight() {
        GLCALL(glDeleteTextures(1, &shadowMap));
    }

}