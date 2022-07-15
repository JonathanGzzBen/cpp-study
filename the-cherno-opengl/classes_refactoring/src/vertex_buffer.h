#ifndef CLASSES_REFACTORING_VERTEX_BUFFER_H
#define CLASSES_REFACTORING_VERTEX_BUFFER_H

class VertexBuffer {
 private:
  unsigned int m_RendererID;

 public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};

#endif  // CLASSES_REFACTORING_VERTEX_BUFFER_H
