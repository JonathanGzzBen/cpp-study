#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H
#include "buffer_object.h"
#include "program_object.h"

class VertexArrayObject {
 private:
  unsigned int vao;

 public:
  VertexArrayObject() { glGenVertexArrays(1, &vao); }

  auto SetVertexAttribPointer(unsigned int index, int size, unsigned int type,
                              bool normalized, int stride,
                              const void* pointer) {
    Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
  }

  auto SetVertexAttribDivisor(const unsigned int index,
                              const unsigned int divisor) {
    Bind();
    glVertexAttribDivisor(index, divisor);
  }

  auto BindBuffer(unsigned int target, BufferObject buffer) {
    Bind();
    glBindBuffer(target, buffer.GetBufferName());
  }
  auto UnbindBuffer(unsigned int target) {
    Bind();
    glBindBuffer(target, 0);
  }

  auto Bind() -> void { glBindVertexArray(vao); }
  auto Unbind() -> void { glBindVertexArray(0); }
};
#endif  // VERTEX_ARRAY_OBJECT_H