#ifndef LIGHT_H
#define LIGHT_H

#include "transform.h"
#include "../renderer/texture.h"

namespace Bubble {

    class Light {
    public:
        Vec3 color;
        Transform& transform;
        f32 intensity = 1.0f;
        enum Type {
            Directional,
            Point,
        } type;

    protected:
        Light(Transform& t, const Vec3& color, f32 intensity): transform(t), color(color), intensity(intensity) { }

    };

    class DirectionalLight : public Light {
    public:
        DirectionalLight(Transform& t, const Vec3& color, f32 intensity): Light(t, color, intensity) { type = Directional; }
        void GenerateShadowMap(bool value);

        inline u32 GetShadowMap() const { return shadowMap; } 
        inline u32 GetShadowMapSize() const { return shadowMapSize; } 
        inline bool GetGenerateShadowMap() const { return generateShadowMap; }
        Mat4 GetLightMatrix() const;

        DirectionalLight::~DirectionalLight();

    private:
        u32 shadowMap = 0;
        u32 shadowMapSize = 4096;
        bool generateShadowMap = false;
    };


}

#endif /* End of LIGHT_H */