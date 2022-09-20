#include <iostream>
#include <fstream>
#include <streambuf>

#include "shaderProgram.h"
#include "../core/errors.h"

namespace Bubble {

    void ShaderProgram::Init(const std::map<GLenum, std::string>& mapSources) {
        this->mapSources = mapSources;
    }

    void ShaderProgram::Compile() {
        for (auto& element: mapSources) {
            std::ifstream t(element.second);
     	    std::string sourcecpp;
     	    t.seekg(0, std::ios::end);   
     	    sourcecpp.reserve(t.tellg());
     	    t.seekg(0, std::ios::beg);
     	    sourcecpp.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

            GLCALL(mapShaders[element.first] = glCreateShader(element.first));
            GLuint& shader_descriptor = mapShaders[element.first];

     	    const char* source =  sourcecpp.c_str();
     	    // binding the source code of the shader to the shaders object (shader, number of lines, shader text, NULL)
     	    GLCALL(glShaderSource(shader_descriptor, 1, &source, NULL));  
     	    GLCALL(glCompileShader(shader_descriptor)); 

     	    // checking for compilation errors
     	    GLint success;
     	    GLCALL(glGetShaderiv(shader_descriptor, GL_COMPILE_STATUS, &success));
     	    if(!success) {
                 GLint logLen;
                 GLCALL(glGetShaderiv(shader_descriptor, GL_INFO_LOG_LENGTH, &logLen));
                 if (logLen > 0) {
                    char *infoLog = new char[logLen];
                    GLCALL(glGetShaderInfoLog(shader_descriptor, logLen, NULL, infoLog));
                    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
                    delete[] infoLog;
                }
     	    }
        }
    }

    void ShaderProgram::Link() {
     	GLCALL(descriptor = glCreateProgram());

        for (auto& element: mapShaders) {
            GLCALL(glAttachShader(descriptor, element.second));
        }
     	GLCALL(glLinkProgram(descriptor));

     	// checking for linking errors
     	GLint success;
     	GLCALL(glGetProgramiv(descriptor, GL_LINK_STATUS, &success));
     	if (!success) {
            GLint logLen;
            GLCALL(glGetProgramiv(descriptor, GL_INFO_LOG_LENGTH, &logLen));
            if (logLen > 0) {
                char *infoLog = new char[logLen];
     		    GLCALL(glGetProgramInfoLog(descriptor, logLen, NULL, infoLog));
                std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
                delete[] infoLog;
            }
     	}
    }

    void ShaderProgram::Run() const {
        GLCALL(glUseProgram(descriptor));
    }

    void ShaderProgram::SetUniform(const char* name, const Mat4& mat) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, mat.GetData()));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, const Mat3& mat) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniformMatrix3fv(location, 1, GL_FALSE, mat.GetData()));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, const Vec4& vec) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, const Vec3& vec) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniform3f(location, vec.x, vec.y, vec.z));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, const Vec2& vec) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name));  
        GLCALL(glUniform2f(location, vec.x, vec.y));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, f32 value) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniform1f(location, value));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, i32 value) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name)); 
        GLCALL(glUniform1i(location, value));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, u32 value) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name));  
        GLCALL(glUniform1ui(location, value));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }

    void ShaderProgram::SetUniform(const char* name, i32* values, u32 size) const {
        GLint location;
        GLCALL(location = glGetUniformLocation(descriptor, name));
        GLCALL(glUniform1iv(location, size, values));
        if (location == -1) {
            fprintf(stderr, "Uniform %s %d not found\n", name, location);
            exit(EXIT_FAILURE);
        }
    }


    ShaderProgram::~ShaderProgram() {
        for (auto& element: mapShaders) {
     	    GLCALL(glDeleteShader(element.second));
        }
        if (descriptor)
            GLCALL(glDeleteProgram(descriptor));
    } 

}