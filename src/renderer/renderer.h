#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "../third_party/stb_truetype.h"

#include "../window/window.h"
#include "../core/types.h"
#include "shaderProgram.h"
#include "font.h"
#include "../window/framebuffer.h"
#include "../scene/light.h"

namespace Bubble {
    class GraphicsComponent;
    class Camera;

    // due to std140 standart array element should be multiple of 4 bytes
    struct DirLightData {
        Mat4 lightMatrix;
        Vec3 direction; 
        bool hasShadowMap;
        Vec3 color;
        f32 intensity;
    };

    struct DirLightBatch {
        DirLightData dirLights[32]; 
        i32 cntLights;
    };

    class Renderer {
    public:
        inline static Renderer* GetInstance() { if (!instance) instance = new Renderer(); return instance; }

        inline void SetMainCamera(Camera* c) { mainCamera = c; }

        void RegisterGraphicsComponent(GraphicsComponent* graphicsComponent);
        void DeregisterGraphicsComponent(GraphicsComponent* graphicsComponent);

        void RegisterDirectionalLight(DirectionalLight* directionalLight);
        void DeregisterDirectionalLight(DirectionalLight* directionalLight);

        void Init();
        void ResizeFramebuffer(f32 width, f32 height);
        void Draw();
        void DrawText(const Font& font, f32 x, f32 y, const char* text); // x, y - screen coords in pixels

        ~Renderer();

    private:
        DirLightBatch dirLightBatch;
        std::vector<GraphicsComponent*> graphicsComponents;
        std::vector<DirectionalLight*> directionalLights;
        ShaderProgram depthProgram;
        ShaderProgram textProgram;
        Camera* mainCamera = nullptr;
        static Renderer* instance;

        u32 shadowBuffer;
        u32 dirLightUBO = 0;

        u32 textIBO = 0;
        u32 textVBO = 0;
        u32 textVAO = 0;
        i32 textBatchSize = 1024;

        Renderer() {}
    };
}

#endif /* End of RENDERER_H */ 