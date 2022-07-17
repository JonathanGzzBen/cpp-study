#ifndef CLASSES_REFACTORING_RENDERER_H
#define CLASSES_REFACTORING_RENDERER_H
#include <cassert>

#ifdef NDEBUG
#define GLCall(x) x;
#else
#define GLCall(x) \
  GLClearError(); \
  x;              \
  assert(GLLogCall(#x, __FILE__, __LINE__));
#endif

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

#endif  // CLASSES_REFACTORING_RENDERER_H
