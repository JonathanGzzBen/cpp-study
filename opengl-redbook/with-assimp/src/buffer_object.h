#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H
#include "GL/glew.h"

class BufferObject {
 private:
  unsigned int buffer_name;

 public:
  BufferObject(void* data, size_t size, int flags = 0) {
    glCreateBuffers(1, &buffer_name);
    glNamedBufferStorage(buffer_name, size, data, flags);
  }
  ~BufferObject() = default;

  auto GetBufferName() const -> unsigned int { return buffer_name; }
};

#endif  // BUFFER_OBJECT_H