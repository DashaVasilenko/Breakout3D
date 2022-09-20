#include <algorithm>

#include "renderer.h"
#include "../core/errors.h"
#include "../scene/gameObject.h"
#include "../scene/camera.h"
#include "../game/app.h"

namespace Bubble{
    struct TextVertex {
        Vec3 position;
        Vec2 uv;
    };

    Renderer* Renderer::instance = nullptr;

    void Renderer::ResizeFramebuffer(f32 width, f32 height) { 
        mainCamera->SetProjection(width/height); 
    }

    void Renderer::RegisterGraphicsComponent(GraphicsComponent* graphicsComponent) {
        graphicsComponents.push_back(graphicsComponent);
    }

    void Renderer::DeregisterGraphicsComponent(GraphicsComponent* graphicsComponent) {
        auto it = std::find(graphicsComponents.begin(), graphicsComponents.end(), graphicsComponent);
        if (it != graphicsComponents.end()) {
            (*it) = graphicsComponents.back();
            graphicsComponents.pop_back();
        }
    }

    void Renderer::RegisterDirectionalLight(DirectionalLight* directionalLight) {
        directionalLights.push_back(directionalLight);
    }

    void Renderer::DeregisterDirectionalLight(DirectionalLight* directionalLight) {
        auto it = std::find(directionalLights.begin(), directionalLights.end(), directionalLight);
        if (it != directionalLights.end()) {
            (*it) = directionalLights.back();
            directionalLights.pop_back();
        }
    }

    void Renderer::Init() {
        Window* window = Window::GetInstance();

        std::map<GLenum, std::string> mapSources;
        mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/text_vertex.glsl";
	    mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/text_fragment.glsl";
	    textProgram.Init(mapSources);
	    textProgram.Compile();
	    textProgram.Link();

        mapSources[GL_VERTEX_SHADER] = Application::path + "/../../data/glsl/shadow_map_depth_vertex.glsl";
	    mapSources[GL_FRAGMENT_SHADER] = Application::path + "/../../data/glsl/shadow_map_depth_fragment.glsl";
	    depthProgram.Init(mapSources);
	    depthProgram.Compile();
	    depthProgram.Link();

        std::vector<u32> indices;
        for (int i = 0; i < 6*textBatchSize; i += 4) {
            indices.push_back(i);
            indices.push_back(i + 2);
            indices.push_back(i + 1);
            indices.push_back(i);
            indices.push_back(i + 3);
            indices.push_back(i + 2);
        }

        GLCALL(glGenBuffers(1, &textVBO));
	    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, textVBO));
	    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertex)*4*textBatchSize, NULL, GL_DYNAMIC_DRAW));

        GLCALL(glGenBuffers(1, &textIBO));
	    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textIBO));
	    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*textBatchSize*sizeof(u32), indices.data(), GL_STATIC_DRAW));

        GLCALL(glGenVertexArrays(1, &textVAO));
	    GLCALL(glBindVertexArray(textVAO));

        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    //attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        u64 stride = 0;
        for (Attribute& attribute: attributes) {
            attribute.offset = stride;
            stride += attribute.elemSize*attribute.count;
        }
        for (const Attribute& attribute: attributes) {
            GLCALL(glVertexAttribPointer(attribute.slot, attribute.count, attribute.type, attribute.normalized, (GLsizei)stride, (GLvoid*)attribute.offset));
	        GLCALL(glEnableVertexAttribArray(attribute.slot));
        }

    	
        GLCALL(glGenFramebuffers(1, &shadowBuffer));
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer));
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        GLCALL(glGenBuffers(1, &dirLightUBO));
	    GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, dirLightUBO));
        GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(DirLightBatch), NULL, GL_DYNAMIC_DRAW));
        GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, dirLightUBO));

        GLCALL(glViewport(0, 0, window->GetWidth(), window->GetHeight()));
        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glEnable(GL_CULL_FACE));
    }
    
    void Renderer::Draw() {
        Window* window = Window::GetInstance();

        // 1. render depth of scene to texture (from light's perspective)
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer));
        depthProgram.Run();

        i32 cntShadowMaps = 0;
        for (DirectionalLight* light: directionalLights) {
            if (cntShadowMaps >= 4) break;
            if (!light->GetGenerateShadowMap()) continue;

            GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, light->GetShadowMap(), 0));
            assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
            GLCALL(glViewport(0, 0, light->GetShadowMapSize(), light->GetShadowMapSize()));
            GLCALL(glClear(GL_DEPTH_BUFFER_BIT));

            for (GraphicsComponent* gc: graphicsComponents) {
                depthProgram.SetUniform("model", gc->transform.GetModelMatrix());
                depthProgram.SetUniform("lightProjectionView", light->GetLightMatrix());
                gc->mesh->BindBuffers();
		        if (gc->mesh->GetIsFromObj()) {
                    GLCALL(glDrawArrays(GL_TRIANGLES, 0, gc->mesh->GetVerticesCount()));
                }
                else {
                    GLCALL(glDrawElements(GL_TRIANGLES, gc->mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0));
                }
            }
            cntShadowMaps++;
        }

        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        // reset viewport
        GLCALL(glViewport(0, 0, window->GetWidth(), window->GetHeight()));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    	GLCALL(glClearColor(0.4f, 0.70196f, 1.0f, 1.0f));

        dirLightBatch.cntLights = std::min(32, (i32)directionalLights.size());
        int j = 6;
        for (int i = 0; i < dirLightBatch.cntLights; i++) {
            dirLightBatch.dirLights[i].lightMatrix = directionalLights[i]->GetLightMatrix();
            dirLightBatch.dirLights[i].direction = directionalLights[i]->transform.GetForward();
            dirLightBatch.dirLights[i].hasShadowMap = directionalLights[i]->GetGenerateShadowMap();
            dirLightBatch.dirLights[i].color = directionalLights[i]->color;
            dirLightBatch.dirLights[i].intensity = directionalLights[i]->intensity;

            if (dirLightBatch.dirLights[i].hasShadowMap && j < 10) {
                GLCALL(glActiveTexture(GL_TEXTURE0 + j));
                GLCALL(glBindTexture(GL_TEXTURE_2D, directionalLights[i]->GetShadowMap()));
                j++;
            }
        }
        GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, dirLightUBO));
        GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(DirLightBatch), &dirLightBatch));

        Mat4 projection = mainCamera->GetProjectionMatrix();
        Mat4 view = mainCamera->GetViewMatrix();

        for (GraphicsComponent* gc: graphicsComponents) {
            if (gc->material->GetDrawWireframe()) {
                GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
            }
            gc->material->BindMaterial(projection, view, gc->transform.GetModelMatrix()); 
            gc->mesh->BindBuffers();
            if (gc->mesh->GetIsFromObj()) {
                GLCALL(glDrawArrays(GL_TRIANGLES, 0, gc->mesh->GetVerticesCount()));
            }
            else {
                GLCALL(glDrawElements(GL_TRIANGLES, gc->mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0));
            }
            if (gc->material->GetDrawWireframe()) {
                GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
            }
        }
    } 

    void Renderer::DrawText(const Font& font, f32 x, f32 y, const char* text) {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, textVBO));
        TextVertex* textBatch;
        GLCALL(textBatch = (TextVertex*)glMapBuffer(GL_ARRAY_BUFFER,  GL_WRITE_ONLY));

        int currentBatchSize = 0;

        textProgram.Run();
        f32 width = (f32)Window::GetInstance()->GetWidth();
        f32 height = (f32)Window::GetInstance()->GetHeight();
        Mat4 projection = Orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        Vec4 v = projection*Vec4(width, height, 0.0f, 1.0f);
        textProgram.SetUniform("projection", projection);
        GLCALL(glActiveTexture(GL_TEXTURE0)); 
        GLCALL(glBindTexture(GL_TEXTURE_2D, font.GetBitmapHandle()));
        GLCALL(glBindVertexArray(textVAO));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textIBO));

        while (*text) {
            if (*text >= 32 && *text < 128) {
                stbtt_aligned_quad q;
                stbtt_GetBakedQuad(font.GetCharacterData(), font.GetBitmapWidth(), font.GetBitmapHeight(), *text-32, &x, &y, &q, 1); //1=opengl & d3d10+,0=d3d9

                textBatch->position = Vec3(q.x0, q.y0, 0.0f);
                textBatch->uv = Vec2(q.s0, q.t0);
                textBatch++;

                textBatch->position = Vec3(q.x1, q.y0, 0.0f);
                textBatch->uv = Vec2(q.s1, q.t0);
                textBatch++;

                textBatch->position = Vec3(q.x1, q.y1, 0.0f);
                textBatch->uv = Vec2(q.s1, q.t1);
                textBatch++;

                textBatch->position = Vec3(q.x0, q.y1, 0.0f);
                textBatch->uv = Vec2(q.s0, q.t1);
                textBatch++;     
                
                currentBatchSize++;
                if (currentBatchSize == textBatchSize) {
                    GLCALL(glUnmapBuffer(GL_ARRAY_BUFFER));
                    GLCALL(glDrawElements(GL_TRIANGLES, currentBatchSize*6, GL_UNSIGNED_INT, 0));
                    GLCALL(textBatch = (TextVertex*)glMapBuffer(GL_ARRAY_BUFFER,  GL_WRITE_ONLY));
                    currentBatchSize = 0;
                }

            }
            ++text;
        }

        GLCALL(glUnmapBuffer(GL_ARRAY_BUFFER));
        if (currentBatchSize > 0)
            GLCALL(glDrawElements(GL_TRIANGLES, currentBatchSize*6, GL_UNSIGNED_INT, 0));
    }

    Renderer::~Renderer() {
        if (textVAO) { GLCALL(glDeleteVertexArrays(1, &textVAO)); }
        if (textVBO) { GLCALL(glDeleteBuffers(1, &textVBO)); }  
        if (textIBO) { GLCALL(glDeleteBuffers(1, &textIBO)); }
        if (shadowBuffer) { GLCALL(glDeleteFramebuffers(1, &shadowBuffer)); }
    }

}