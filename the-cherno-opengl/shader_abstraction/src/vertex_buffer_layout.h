#ifndef BUFFER_LAYOUT_VERTEX_BUFFER_LAYOUT_H
#define BUFFER_LAYOUT_VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>

#include <cassert>
#include <vector>

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
        return 4;
      case GL_UNSIGNED_INT:
        return 4;
      case GL_UNSIGNED_BYTE:
        return 1;
      default:
        assert(false);
        return 0;
    }
  }
};

class VertexBufferLayout {
 private:
  unsigned int m_Stride;
  std::vector<VertexBufferElement> m_Elements;

 public:
  VertexBufferLayout() : m_Stride{0} {};

  template <typename T>
  void Push(unsigned int count) {}

  template <>
  void Push<float>(unsigned int count) {
    m_Elements.push_back(VertexBufferElement{
        .type = GL_FLOAT, .count = count, .normalized = GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
  }

  template <>
  void Push<unsigned int>(unsigned int count) {
    m_Elements.push_back(VertexBufferElement{
        .type = GL_UNSIGNED_INT, .count = count, .normalized = GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
  }

  template <>
  void Push<unsigned char>(unsigned int count) {
    m_Elements.push_back(VertexBufferElement{
        .type = GL_UNSIGNED_BYTE, .count = count, .normalized = GL_TRUE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
  }

  inline const std::vector<VertexBufferElement> GetElements() const {
    return m_Elements;
  }
  inline unsigned int GetStride() const { return m_Stride; }
};

#endif  // BUFFER_LAYOUT_VERTEX_BUFFER_LAYOUT_H
