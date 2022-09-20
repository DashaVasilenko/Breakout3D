#ifndef FONT_H
#define FONT_H

#include <GL/glew.h>

#include "../third_party/stb_truetype.h"

#include "../core/types.h"

namespace Bubble {

    class Font {
    public:
        void LoadFont(const char* path, f32 fontSize);

        GLuint GetBitmapHandle() const { return fontTexture; }
        const stbtt_bakedchar* GetCharacterData() const { return cdata; }
        i32 GetBitmapWidth() const { return width; }
        i32 GetBitmapHeight() const { return height; }

        ~Font();
        
    private:
        stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
        GLuint fontTexture;
        i32 width = 1024;
        i32 height = 1024;
    };
}

#endif /* End of FONT_H */