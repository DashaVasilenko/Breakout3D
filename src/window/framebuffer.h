#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

#include "../core/types.h"

namespace Bubble {

    class ShadowBuffer {
    public:
        ShadowBuffer();
        void BufferInit(i32 width, i32  height);
        void Bind();
        void BindDepth();
        void Unbind() const;
        void LightPassBind() const;

        u32 GetSize() { return size; }
        GLuint GetDescriptor() const { return descriptor; }
        u32 GetDepthMap() const { return depthMap; }

        ~ShadowBuffer();

    private:
        GLuint descriptor;
        u32 depthMap;
        u32 size = 512; // map size
    };

}

#endif /* End of FRAMEBUFFER_H */