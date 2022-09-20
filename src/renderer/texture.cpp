#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "../core/errors.h"

namespace Bubble {
    Texture::Texture() {
        GLCALL(glGenTextures(1, &descriptor));
    }

    void Texture::Bind() const {
        GLCALL(glBindTexture(GL_TEXTURE_2D, descriptor));
    }

    void Texture::Unbind() const { 
        GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    Texture::~Texture() {
        GLCALL(glDeleteTextures(1, &descriptor));
    }

    //-----------------------------------------------------------------------------------------------------------
    void Texture2D::CreateAttachment(GLenum slot) const {
        GLCALL(glActiveTexture(slot));
        GLCALL(glBindTexture(GL_TEXTURE_2D, descriptor)); 
    }

    void Texture2D::Init(const std::string& filename) {
        image = stbi_load(filename.c_str(), &width, &height, &cnt, 3);
        Bind();
    	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
    	GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    	stbi_image_free(image);
        Unbind();
    }

    //-----------------------------------------------------------------------------------------------------------
    void CubeMap::Init(const std::array<std::string, 6>& fileNames) {
        Bind();
        for(unsigned int i = 0; i < fileNames.size(); i++)
        {
            image = stbi_load(fileNames[i].c_str(), &width, &height, &nrChannels, 0);
            if (image) {
                GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
            }
            else {
                std::cout << "Cubemap texture failed to load at path: " << fileNames[i] << std::endl;
                stbi_image_free(image);
            }
        }

        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE)); 
    }

    //------------------------------------------------------------------------------------------------------
    void RenderTexture:: CreateAttachment(GLenum slot) const {
        GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, slot, GL_TEXTURE_2D, descriptor, 0)); 
    }

    void RenderTexture::Init(int width, int height, GLuint internalformat, GLenum format, GLenum type, GLint param) {
        Bind();
        this->width = width;
        this->height = height;
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, type, NULL));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param));
    }

    void RenderTexture::InitDepthMap(int width, int height) {
        Bind();
        this->width = width;
        this->height = height;
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        GLCALL(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
    }

    void RenderTexture::InitBrightMapGauss(int width, int height) {
        Bind();
        this->width = width;
        this->height = height;
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }
}