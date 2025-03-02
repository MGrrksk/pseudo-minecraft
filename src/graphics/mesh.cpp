#include <graphics/mesh.hpp>

Mesh::Mesh(float vertices[], unsigned int size, unsigned int attributes) {
    int stride = (
        (attributes & MESH_ATTR_POSITION ? 3 : 0) +
        (attributes & MESH_ATTR_COLOR ? 3 : 0) +
        (attributes & MESH_ATTR_TEXCOORD ? 2 : 0)
    ) * sizeof(float);
    count = size / stride;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    int attrIndex = 0;
    if (attributes & MESH_ATTR_POSITION) {
        glVertexAttribPointer(attrIndex, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(attrIndex);
        attrIndex++;
    }
    if (attributes & MESH_ATTR_COLOR) {
        glVertexAttribPointer(attrIndex, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(attrIndex);
        attrIndex++;
    }
    if (attributes & MESH_ATTR_TEXCOORD) {
        glVertexAttribPointer(attrIndex, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(attrIndex);
        attrIndex++;
    }
}
Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, count);
}