#ifndef MESH_H
#define MESH_H

#include <vector>

#include "../core/errors.h"
#include "../core/types.h"

namespace Bubble {

    struct Attribute {
        u32 slot;
        u32 count;
        GLenum type;
        bool normalized;
        u32 elemSize;
        u64 offset;
    };

    class Mesh {
    public:
        inline u32 GetIndicesCount() const { return indicesCount; }
        inline u32 GetVerticesCount() const { return verticesCount; }
        inline bool GetIsFromObj() const { return isObj; }

        void Create(void* vertices, u64 vertices_size, u32* indices, u64 indices_count, std::vector<Attribute>& attributes);
        void Create(void* vertices, u64 vertices_size, std::vector<Attribute>& attributes);
        void BindBuffers();
        ~Mesh();

        static Mesh* CreateQuad(f32 size_x = 1.0f, f32 size_y = 1.0f);
        static Mesh* CreateBox(f32 size_x = 1.0f, f32 size_y = 1.0f, f32 size_z = 1.0f);
        static Mesh* CreateSphere(f32 radius = 1.0f, i32 rings = 7, i32 sectors = 7);
        static Mesh* CreateBrick(f32 radiusIn = 1.0f, f32 radiusOut = 2.0f, f32 angle = 45.0f, i32 sectors = 10.0f, f32 height = 1.0f);
        static Mesh* CreateFromObj(const char* path);

    private:
        u32 IBO = 0;
        u32 VBO = 0;
        u32 VAO = 0;
        u32 indicesCount = 0;
        u32 verticesCount = 0;
        bool isObj = false;
    };

}

#endif /* End of MESH_H */