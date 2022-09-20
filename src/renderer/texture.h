#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <array>
#include <GL/glew.h>
#include "../third_party/stb_image.h"

namespace Bubble {
    class Texture {
    public:
        Texture();
        void Bind() const;
        void Unbind() const;
        GLuint GetDescriptor() { return descriptor; }
        ~Texture();

    protected:
        unsigned char* image;
        GLuint descriptor;
        int width;
        int height;
        int cnt;
    };

    class Texture2D : public Texture {
    public:
        void CreateAttachment(GLenum slot) const;
        void Init(const std::string& filename);
    };

    class CubeMap : public Texture{ 
    public:
        void Init(const std::array<std::string, 6>& fileNames);

    private:
        int nrChannels;
    };

    class RenderTexture : public Texture {
    public:
        void CreateAttachment(GLenum slot) const;
        void Init(int width, int height, GLuint internalformat, GLenum format, GLenum type, GLint param);
        void InitDepthMap(int width, int height);
        void InitBrightMapGauss(int width, int height);
    };

}

#endif /* End of TEXTURE_H */