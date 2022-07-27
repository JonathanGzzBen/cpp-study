#pragma once

#include <GL/glew.h>

#include <cassert>

#include "index_buffer.h"
#include "shader.h"
#include "vertex_array.h"

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