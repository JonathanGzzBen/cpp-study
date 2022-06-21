#include "mesh.h"

Mesh::Mesh() : vao{0}, vbo{0}, ibo{0}, indexCount{0} {}

Mesh::~Mesh() { ClearMesh(); }

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices,
                      unsigned int numOfVertices, unsigned int numOfIndices) {
  indexCount = numOfIndices;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices,
               indices, GL_STATIC_DRAW);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::RenderMesh() const {
  glBindVertexArray(vao);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void Mesh::ClearMesh() {
  if (ibo != 0) {
    glDeleteBuffers(1, &ibo);
    ibo = 0;
  }
  if (vbo != 0) {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }
  if (vao != 0) {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }
  indexCount = 0;
}
