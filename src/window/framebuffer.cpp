#include <cstdio>

#include "framebuffer.h"

namespace Bubble {
    
    ShadowBuffer::ShadowBuffer() {
        glGenFramebuffers(1, &descriptor);
    }

    void ShadowBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, descriptor);
    }

    void ShadowBuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ShadowBuffer::BufferInit(i32 width, i32  height) {
        Bind();

        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size, size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);  
        glReadBuffer(GL_NONE);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
        Unbind();
    }

    void ShadowBuffer::BindDepth() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
    }

    void ShadowBuffer::LightPassBind() const {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, depthMap);
    }

    ShadowBuffer::~ShadowBuffer() {
        glDeleteFramebuffers(1, &descriptor);
    } 

}