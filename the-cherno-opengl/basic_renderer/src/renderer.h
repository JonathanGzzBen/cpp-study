#ifndef CLASSES_REFACTORING_RENDERER_H
#define CLASSES_REFACTORING_RENDERER_H

#include <cassert>

#include "src/index_buffer.h"
#include "src/shader.h"
#include "src/vertex_array.h"

#ifdef NDEBUG
#define GLCall(x) x;
#else
#define GLCall(x) \
  GLClearError(); \
  x;              \
  assert(GLLogCall(#x, __FILE__, __LINE__));
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
 public:
  void Clear() const;
  void Draw(const VertexArray& va, const IndexBuffer& ib,
            const Shader& shader) const;
};

#endif  // CLASSES_REFACTORING_RENDERER_H
