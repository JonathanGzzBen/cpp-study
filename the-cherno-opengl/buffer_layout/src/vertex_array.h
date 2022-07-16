#ifndef BUFFER_LAYOUT_VERTEX_ARRAY_H
#define BUFFER_LAYOUT_VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
class VertexArray {
 private:
  unsigned int m_RendererID;

 public:
  VertexArray();
  virtual ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
  void Bind() const;
  void Unbind() const;
};

#endif  // BUFFER_LAYOUT_VERTEX_ARRAY_H
