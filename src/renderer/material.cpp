#include "material.h"
#include "../core/errors.h"

namespace Bubble {
    void PhongMaterial::BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) {
        program->Run();
        i32 slots[] = { 6, 7, 8, 9 }; 
        program->SetUniform("shadowMaps", slots, 4);
        program->SetUniform("Projection", projection);
		program->SetUniform("View", view);
        program->SetUniform("Model", model);

		program->SetUniform("ambientColor", ambientColor);
		program->SetUniform("diffuseColor", diffuseColor);
        program->SetUniform("specularColor", specularColor);
        program->SetUniform("shininess", shininess);
    }

    void PhongTextureMaterial::BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) {
        program->Run();
        program->Run();
        i32 slots[] = { 6, 7, 8, 9 }; 
        program->SetUniform("shadowMaps", slots, 4);
        program->SetUniform("Projection", projection);
		program->SetUniform("View", view);
        program->SetUniform("Model", model);

        ambientColor->CreateAttachment(GL_TEXTURE0);
        diffuseColor->CreateAttachment(GL_TEXTURE1);
        specularColor->CreateAttachment(GL_TEXTURE2);
        program->SetUniform("shininess", shininess);
        program->SetUniform("tiling", tiling);
    }

    void PhongTextureFloorMaterial::BindMaterial(const Mat4& projection, const Mat4& view, const Mat4& model) {
        program->Run();
        i32 slots[] = { 6, 7, 8, 9 }; 
        program->SetUniform("shadowMaps", slots, 4);
        program->SetUniform("Projection", projection);
		program->SetUniform("View", view);
        program->SetUniform("Model", model);

        ambientColor->CreateAttachment(GL_TEXTURE0);
        diffuseColor->CreateAttachment(GL_TEXTURE1);
        specularColor->CreateAttachment(GL_TEXTURE2);
        //normalMap->CreateAttachment(GL_TEXTURE3);
        program->SetUniform("shininess", shininess);
    }

}