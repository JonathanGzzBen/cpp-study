#ifndef SRC_MESH_H
#define SRC_MESH_H

#include <GL/glew.h>

class Mesh {
 public:
  Mesh();
  ~Mesh();

  void CreateMesh(GLfloat *vertices, unsigned int *indices,
                  unsigned int numOfVertices, unsigned int numOfIndices);
  void RenderMesh() const;
  void ClearMesh();

 private:
  GLuint vao;
  GLuint vbo;
  GLuint ibo;
  GLsizei indexCount;
};

#endif  // SRC_MESH_H