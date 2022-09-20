#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>
#include <cassert>
#include <GL/glew.h>

// set this variable in cmake !!!
//#define DEBUG_BUILD 

#ifdef DEBUG_BUILD
#define GLCALL(x) GLClearError();\
    x;\
    assert(GLLogCall());

static inline void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static inline bool GLLogCall() {
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL_Error] (" << error << ")" << std::endl;
        return false;
	}
    return true;
}
#else
#define GLCALL(x) x
#endif

#endif