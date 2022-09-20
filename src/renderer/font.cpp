#include <string>

#define STB_TRUETYPE_IMPLEMENTATION
#include "font.h"
#include "../core/errors.h"

namespace Bubble {

    void Font::LoadFont(const char* path, f32 fontSize) {
        unsigned char* temp_bitmap = (unsigned char*)malloc(width*height*sizeof(unsigned char));
    
        FILE* file;
        if (fopen_s(&file, path, "rb") != 0) {
            printf("could not open file '%s' \n", path);
            return;
        }

        // obtain file size:
        fseek(file , 0 , SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        // allocate memory to contain the whole file:
        char* buffer = (char*)malloc(sizeof(char)*fileSize);
        if (buffer == NULL) {
            printf("Memory error\n");
            return;
        }

        // copy the file into the buffer:
        size_t result = fread(buffer, 1, fileSize, file);
        if (result != fileSize) {
            printf("Reading error\n");
            return;
        }

        stbtt_BakeFontBitmap((const unsigned char*)buffer, 0, fontSize, temp_bitmap, width, height, 32, 96, cdata); // no guarantee this fits!

        GLCALL(glGenTextures(1, &fontTexture));
        GLCALL(glBindTexture(GL_TEXTURE_2D, fontTexture));
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        // terminate
        fclose(file);
        free(buffer);
        free(temp_bitmap);
        return;
    }

    Font::~Font() {
        if (fontTexture)
            GLCALL(glDeleteTextures(1, &fontTexture));
    }
}