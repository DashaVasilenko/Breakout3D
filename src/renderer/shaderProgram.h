#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <map>

#include "../window/window.h"
#include "../math/vector.h"
#include "../math/matrix.h"

namespace Bubble {
    class ShaderProgram {
    public:
        void Init(const std::map<GLenum, std::string>&);
        void Compile();
        void Link();
        void Run() const;

        void SetUniform(const char* name, const Mat4& mat) const;
        void SetUniform(const char* name, const Mat3& mat) const;
        void SetUniform(const char* name, const Vec4& vec) const;
        void SetUniform(const char* name, const Vec3& vec) const;
        void SetUniform(const char* name, const Vec2& vec) const;
        void SetUniform(const char* name, f32 value) const;
        void SetUniform(const char* name, i32 value) const;
        void SetUniform(const char* name, u32 value) const;
        void SetUniform(const char* name, i32* values, u32 size) const;

        ~ShaderProgram();

    private:
        std::map<GLenum, std::string> mapSources;
        std::map<GLenum, GLuint> mapShaders;
        GLuint descriptor = 0;
    };
}

#endif /* End of SHADERPROGRAM_H */ 