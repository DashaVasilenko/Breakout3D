#define TINYOBJLOADER_IMPLEMENTATION
#include "../third_party/tiny_obj_loader.h"

#include "mesh.h"
#include "../math/matrix.h"
#include "../math/functions.h"

namespace Bubble {
    void Mesh::Create(void* vertices, u64 vertices_size, u32* indices, u64 indices_count, std::vector<Attribute>& attributes) {
	    indicesCount = (u32)indices_count;

        GLCALL(glGenBuffers(1, &VBO));
	    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW));

        GLCALL(glGenBuffers(1, &IBO));
	    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count*sizeof(u32), indices, GL_STATIC_DRAW));

        GLCALL(glGenVertexArrays(1, &VAO));
	    GLCALL(glBindVertexArray(VAO));

        u64 stride = 0;
        for (Attribute& attribute: attributes) {
            attribute.offset = stride;
            stride += attribute.elemSize*attribute.count;
        }
        for (const Attribute& attribute: attributes) {
            GLCALL(glVertexAttribPointer(attribute.slot, attribute.count, attribute.type, attribute.normalized, (GLsizei)stride, (GLvoid*)attribute.offset));
	        GLCALL(glEnableVertexAttribArray(attribute.slot));
        }
    }

    void Mesh::Create(void* vertices, u64 vertices_size, std::vector<Attribute>& attributes) {
        isObj = true;

        GLCALL(glGenBuffers(1, &VBO));
	    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW));

        GLCALL(glGenVertexArrays(1, &VAO));
	    GLCALL(glBindVertexArray(VAO));

        u64 stride = 0;
        for (Attribute& attribute: attributes) {
            attribute.offset = stride;
            stride += attribute.elemSize*attribute.count;
        }
        verticesCount = (u32)(vertices_size/stride);

        for (const Attribute& attribute: attributes) {
            GLCALL(glVertexAttribPointer(attribute.slot, attribute.count, attribute.type, attribute.normalized, (GLsizei)stride, (GLvoid*)attribute.offset));
	        GLCALL(glEnableVertexAttribArray(attribute.slot));
        }
    }

    void Mesh::BindBuffers() {
        if (!isObj) {
            GLCALL(glBindVertexArray(VAO));
            GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
        }
        else {
            GLCALL(glBindVertexArray(VAO));
        }
    }

    Mesh::~Mesh() {
        GLCALL(glDeleteVertexArrays(1, &VAO));
        GLCALL(glDeleteBuffers(1, &IBO));
        GLCALL(glDeleteBuffers(1, &VBO));
    }

    Mesh* Mesh::CreateQuad(f32 size_x, f32 size_y) {
        f32 x = size_x*0.5f;
        f32 y = size_y*0.5f;
        f32 vertices[] = {
            -x,  y, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             x,  y, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
             x, -y, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	        -x, -y, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	    };  

	    u32 indices[] = {
	    	0, 2, 1,
	    	0, 3, 2
	    };

        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        Mesh* mesh = new Mesh();
        mesh->Create(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(u32), attributes);
        return mesh;
    }

    Mesh* Mesh::CreateBox(f32 size_x, f32 size_y, f32 size_z) {
        f32 x = size_x*0.5f;
        f32 y = size_y*0.5f;
        f32 z = size_z*0.5f;
        f32 vertices[] = { // position, normal, uv
            -x, -y,  z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // front face bottom left     0
             x, -y,  z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // front face bottom right    1
            -x,  y,  z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // front face top left        2
             x,  y,  z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // front face top right       3

            -x, -y, -z, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // back face bottom left     4
             x, -y, -z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // back face bottom right    5
            -x,  y, -z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // back face top left        6
             x,  y, -z, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // back face top right       7

             x, -y,  z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // right face bottom left     8
             x, -y, -z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // right face bottom right    9
             x,  y,  z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // right face top left       10
             x,  y, -z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // right face top right      11

            -x, -y,  z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // left face bottom left    12
            -x, -y, -z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // left face bottom right   13
            -x,  y,  z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // left face top left       14
            -x,  y, -z, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // left face top right      15
            
            -x,  y,  z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top face bottom left      16
             x,  y,  z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top face bottom right     17
            -x,  y, -z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top face top left         18
             x,  y, -z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top face top right        19

            -x, -y,  z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom face bottom left  20
             x, -y,  z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom face bottom right 21
            -x, -y, -z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // bottom face top left     22
             x, -y, -z, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bottom face top right    23
	    };

        u32 indices[] = {  0,  1,  2,  
    				       1,  3,  2,
                           4,  6,  5,
                           5,  6,  7,
                           8,  9, 10,
                           9, 11, 10,
                          12, 14, 13,
                          13, 14, 15,
                          16, 17, 18,
                          17, 19, 18, 
                          20, 22, 21, 
                          21, 22, 23	      
	    };  

        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        Mesh* mesh = new Mesh();
        mesh->Create(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(u32), attributes);
        return mesh;
    }

    struct Vertex {
        Vec3 position;
        Vec3 normal;
        Vec2 uv;
    };

    Mesh* Mesh::CreateSphere(f32 radius, i32 rings, i32 sectors) {
        assert(rings > 3 && sectors > 3);
        f32 const R = 1.0f/(rings - 1.0f);
        f32 const S = 1.0f/(sectors - 1.0f);
        std::vector<Vertex> vertices;
        std::vector<u32> indices;

        //  create north pole
        vertices.push_back({ {0.0f, radius, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} });
        // create vertices
        for (i32 r = 1; r < rings - 1; r++) {
            for (i32 s = 0; s < sectors; s++) {
                f32 const phi = 2.0f*(f32)M_PI*s*S;
                f32 const theta = (f32)M_PI*r*R;

                Vec3 normal;
                normal.x = sin(theta)*cos(phi);
                normal.y = cos(theta);
                normal.z = sin(theta)*sin(phi);
                Vec3 position = normal*radius;
                Vec2 uv = Vec2(s*S, r*R);
                vertices.push_back({ position, normal, uv });     
            }
        }
        // create south pole
        vertices.push_back({ {0.0f, -radius, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} });

        // connecting north pole
        for (i32 s = 1; s < sectors; s++) {
            indices.push_back(0);
            indices.push_back(s + 1);
            indices.push_back(s);
        }
        // connecting other vertices
        for (i32 r = 0; r < rings - 3; r++) {
            i32 currentRingBegin = 1 + (sectors)*r;
            i32 nextRingBegin = 1 + (sectors)*(r + 1);
            for (i32 s = 0; s < sectors - 1; s++) {
                indices.push_back(nextRingBegin + s);
                indices.push_back(currentRingBegin + s);
                indices.push_back(nextRingBegin + s + 1);

                indices.push_back(currentRingBegin + s);
                indices.push_back(currentRingBegin + s + 1);
                indices.push_back(nextRingBegin + s + 1);
            }
        }
        // connecting south pole
        u32 southPole = (u32)(vertices.size() - 1);
        for (i32 s = 1; s < sectors; s++) {
            indices.push_back(southPole);
            indices.push_back(southPole - s - 1);
            indices.push_back(southPole - s);
        }

        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        Mesh* mesh = new Mesh();
        mesh->Create(vertices.data(), vertices.size()*sizeof(Vertex), indices.data(), indices.size(), attributes);
        return mesh;
    }

    Mesh* Mesh::CreateBrick(f32 radiusIn, f32 radiusOut, f32 angle, i32 sectors, f32 height) {
        assert(sectors > 1);
        f32 const S = 1.0f/(sectors - 1.0f);
        f32 const a = Radians(angle);
        f32 const h = height*0.5f;
        std::vector<Vertex> vertices;
        std::vector<u32> indices;

        f32 sin = sinf(Radians(angle*0.5f));
        f32 cos = cosf(Radians(angle*0.5f));
        //Mat3 rotation = Mat3({cos, 0.0f,  sin}, {0.0f, 1.0f, 0.0f}, {-sin, 0.0f, cos});
        Mat3 rotation = Mat3({cos, 0.0f,  -sin}, {0.0f, 1.0f, 0.0f}, {sin, 0.0f, cos});

        //-------------------------------------------------------------------------------
        //                           create left lateral face
        //-------------------------------------------------------------------------------
        // left lateral side bottom outer point 0
        Vec3 normal = rotation*Vec3(1.0f, 0.0f, 0.0f);
        Vec3 position = Vec3(normal.x*radiusOut, -h, normal.z*radiusOut);
        Vec2 uv = Vec2(0.0f, 0.0f);
        vertices.push_back({ position, Vec3(0.0f, 0.0f, 1.0f), uv });  

        // left lateral side top outer point 1
        position = Vec3(normal.x*radiusOut, h, normal.z*radiusOut);
        uv = Vec2(0.0f, 1.0f);
        vertices.push_back({ position, Vec3(0.0f, 0.0f, 1.0f), uv }); 

        // left lateral side bottom inner point 2
        position = Vec3(normal.x*radiusIn, -h, normal.z*radiusIn);
        uv = Vec2(1.0f, 0.0f);
        vertices.push_back({ position, Vec3(0.0f, 0.0f, 1.0f), uv }); 

        // left lateral side top inner point 3
        position = Vec3(normal.x*radiusIn, h, normal.z*radiusIn);
        uv = Vec2(1.0f, 1.0f);
        vertices.push_back({ position, Vec3(0.0f, 0.0f, 1.0f), uv }); 

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(1);

        //-------------------------------------------------------------------------------
        //                           create right lateral face
        //-------------------------------------------------------------------------------
        // right lateral side bottom outer point 4
        Vec3 pos = rotation*Vec3(cosf(a), 0.0f, sinf(a));
        normal = rotation*Vec3::cross(pos, Vec3(0.0f, 1.0f, 0.0f));
        position = Vec3(pos.x*radiusOut, -h, pos.z*radiusOut);
        uv = Vec2(1.0f, 0.0f);
        vertices.push_back({ position, normal, uv });  

        // right lateral side top outer point 5
        position = Vec3(pos.x*radiusOut, h, pos.z*radiusOut);
        uv = Vec2(1.0f, 1.0f);
        vertices.push_back({ position, normal, uv }); 

        // right lateral side bottom inner point 6
        position = Vec3(pos.x*radiusIn, -h, pos.z*radiusIn);
        uv = Vec2(0.0f, 0.0f);
        vertices.push_back({ position, normal, uv }); 

        // right lateral side top inner point 7
        position = Vec3(pos.x*radiusIn, h, pos.z*radiusIn);
        uv = Vec2(0.0f, 1.0f);
        vertices.push_back({ position, normal, uv }); 

        indices.push_back(6);
        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(7);

        //-------------------------------------------------------------------------------
        //                          create innner and outer faces
        //-------------------------------------------------------------------------------
        // create innner and outer vertices 
        for (i32 s = 0; s < sectors; s++) {
            f32 const phi = a*s*S;

            // outer face bottom point
            Vec3 normal = rotation*Vec3(cosf(phi), 0.0f, sinf(phi));
            Vec3 position = Vec3(normal.x*radiusOut, -h, normal.z*radiusOut);
            Vec2 uv = Vec2(s*S, 0.0f);
            vertices.push_back({ position, normal, uv });  

            // bottom face outer point
            uv = Vec2(s*S, 0.0f);
            vertices.push_back({ position, Vec3(0.0f, -1.0f, 0.0f), uv }); 

            // outer face top point
            position = Vec3(normal.x*radiusOut, h, normal.z*radiusOut);
            uv = Vec2(s*S, 1.0f);
            vertices.push_back({ position, normal, uv });  

            // top face outer point
            uv = Vec2(s*S, 0.0f);
            vertices.push_back({ position, Vec3(0.0f, 1.0f, 0.0f), uv }); 

            // inner face bottom point
            position = Vec3(normal.x*radiusIn, -h, normal.z*radiusIn);
            uv = Vec2(s*S, 0.0f);
            vertices.push_back({ position, -normal, uv }); 

            // bottom face inner point
            uv = Vec2(s*S, 1.0f);
            vertices.push_back({ position, Vec3(0.0f, -1.0f, 0.0f), uv });

            // inner face top point
            position = Vec3(normal.x*radiusIn, h, normal.z*radiusIn);
            uv = Vec2(s*S, 1.0f);
            vertices.push_back({ position, -normal, uv }); 

            // top face inner point
            uv = Vec2(s*S, 1.0f);
            vertices.push_back({ position, Vec3(0.0f, 1.0f, 0.0f), uv });
        }

        u32 size = (u32)vertices.size() - 8;
        for (u32 i = 8; i < size; i += 8) {
            // outer face
            indices.push_back(i + 8);
            indices.push_back(i + 2);
            indices.push_back(i + 10);

            indices.push_back(i + 8);
            indices.push_back(i);
            indices.push_back(i + 2);

            // inner face
            indices.push_back(i + 4);
            indices.push_back(i + 14);
            indices.push_back(i + 6);

            indices.push_back(i + 4);
            indices.push_back(i + 12);
            indices.push_back(i + 14);

            // bottom face
            indices.push_back(i + 1);
            indices.push_back(i + 13);
            indices.push_back(i + 5);

            indices.push_back(i + 1);
            indices.push_back(i + 9);
            indices.push_back(i + 13);

            // top face
            indices.push_back(i + 3);
            indices.push_back(i + 7);
            indices.push_back(i + 15);

            indices.push_back(i + 3);
            indices.push_back(i + 15);
            indices.push_back(i + 11);
        }

        //-------------------------------------------------------------------------------
        //                          create attributes amd mesh
        //-------------------------------------------------------------------------------
        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        Mesh* mesh = new Mesh();
        mesh->Create(vertices.data(), vertices.size()*sizeof(Vertex), indices.data(), indices.size(), attributes);
        return mesh;
    }

    Mesh* Mesh::CreateFromObj(const char* path) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path, false);

        if (!warn.empty()) {
            printf("%s\n", warn.c_str());
        }

        if (!err.empty()) {
            fprintf(stderr, "%s\n", err.c_str());
        }

        if (!ret) {
            exit(EXIT_FAILURE);
        }

        std::vector<Vertex> vertices;
        //std::vector<u32> indices;
        //std::unordered_map<Vertex, uint32_t> uniqueVertices{};

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;

            //printf("Test: %u\n", (u32)shapes[s].mesh.num_face_vertices.size());
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                int fv = shapes[s].mesh.num_face_vertices[f]; 

                if (fv != 3) {
                    fprintf(stderr, "Face vertices: %u, Error: program supports only triangle meshes.\n", (u32)shapes[s].mesh.num_face_vertices.size());
                    exit(EXIT_FAILURE);
                }

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                    tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                    tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                    tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                    tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                    tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                    tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                    tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
      

                    //indices.push_back(idx.normal_index);
                    vertices.push_back({{vx, vy, vz}, {nx, ny, nz}, {tx, ty}});
                }
                index_offset += fv;   
            }
        }

        std::vector<Attribute> attributes;
	    attributes.push_back({0, 3, GL_FLOAT, false, sizeof(float), 0});
	    attributes.push_back({1, 3, GL_FLOAT, false, sizeof(float), 0});
        attributes.push_back({2, 2, GL_FLOAT, false, sizeof(float), 0});

        Mesh* mesh = new Mesh();
        mesh->Create(vertices.data(), vertices.size()*sizeof(Vertex), attributes);
        return mesh;
    }

}