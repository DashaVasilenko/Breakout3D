#ifndef MATERIAL_H
#define MATERIAL_H

#include "shaderProgram.h"
#include "../math/matrix.h"
#include "texture.h"

namespace Bubble {
    class Material {
    public:
        virtual void BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) = 0;
        void SetDrawWireframe(bool value) { drawWireframe = value; }
        bool GetDrawWireframe() const { return drawWireframe; }
        virtual ~Material() { }
    
    private:
        bool drawWireframe = false;
    };

    class PhongMaterial: public Material {
    public:
        PhongMaterial(const ShaderProgram* program, Vec3 ambient, Vec3 diffuse, Vec3 specular): 
            program(program), ambientColor(ambient), diffuseColor(diffuse), specularColor(specular) { }
        void BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) override;
        inline void SetDiffuseColor(const Vec3& color) { diffuseColor = color; }
        virtual ~PhongMaterial() { }

    private:
        Vec3 ambientColor = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 diffuseColor = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 specularColor = Vec3(1.0f, 0.0f, 0.0f);

        const ShaderProgram* program = nullptr;

        float shininess = 10.0f;
    };

    class PhongTextureMaterial: public Material {
    public:
        PhongTextureMaterial(const ShaderProgram* program, const Texture2D* ambient, const Texture2D* diffuse, 
                             const Texture2D* specular, Vec2 tiling): 
            program(program), ambientColor(ambient), diffuseColor(diffuse), specularColor(specular), tiling(tiling) { }
        void BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) override;
        virtual ~PhongTextureMaterial() { }

    private:
        Vec2 tiling;
        const ShaderProgram* program = nullptr;
        const Texture2D* ambientColor = nullptr;
        const Texture2D* diffuseColor = nullptr;
        const Texture2D* specularColor = nullptr;
        f32 shininess = 10.0f;
    };

    class PhongTextureFloorMaterial: public Material {
    public:
        PhongTextureFloorMaterial(const ShaderProgram* program, const Texture2D* ambient, const Texture2D* diffuse, 
                                  const Texture2D* specular/*, const Texture2D* normal*/): 
            program(program), ambientColor(ambient), diffuseColor(diffuse), specularColor(specular)/*, normalMap(normal)*/ { }
        void BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) override;
        virtual ~PhongTextureFloorMaterial() { }

    private:
        const ShaderProgram* program = nullptr;
        const Texture2D* ambientColor = nullptr;
        const Texture2D* diffuseColor = nullptr;
        const Texture2D* specularColor = nullptr;
        //const Texture2D* normalMap = nullptr;
        f32 shininess = 10.0f;
    };



}

#endif /* End of MATERIAL_H */