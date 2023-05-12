#ifndef MESH_H
#define MESH_H

#include <gl/glew.h>

class Mesh {
 public:
  Mesh() = default;
  ~Mesh();

  void CreateMesh(GLfloat *vertices, unsigned int *indices,
                  unsigned int num_of_vertices, unsigned int num_of_indices);
  void RenderMesh();
  void ClearMesh();

 private:
  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint ibo = 0;
  GLsizei index_count = 0;
};

#endif  // MESH_H