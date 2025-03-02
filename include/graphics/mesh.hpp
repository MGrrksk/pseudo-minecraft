#pragma once
#include <glad/glad.h>

enum MeshAttribute {
    MESH_ATTR_POSITION = 1,
    MESH_ATTR_COLOR = 2,
    MESH_ATTR_TEXCOORD = 4
};

class Mesh {
    unsigned int VBO, VAO;
    unsigned int count;
    public:
        Mesh(float vertices[], unsigned int size, unsigned int attributes);
        ~Mesh();
        void draw();
};