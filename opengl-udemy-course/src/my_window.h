#ifndef MY_WINDOW_H
#define MY_WINDOW_H

// GLEW should be included before other headers
// clang-format off
#include <gl/glew.h>
// clang-format on
#include <GLFW/glfw3.h>

class Window {
 public:
  Window();
  Window(GLint window_width, GLint window_height);
  ~Window();

  int Initialize();
  GLfloat GetBufferWidth() const { return static_cast<GLfloat>(buffer_width); }
  GLfloat GetBufferHeight() const {
    return static_cast<GLfloat>(buffer_height);
  }

  bool GetShouldClose() const { return glfwWindowShouldClose(main_window); }
  void SwapBuffers() const { glfwSwapBuffers(main_window); }

 private:
  GLFWwindow *main_window = nullptr;
  GLint width;
  GLint height;
  GLint buffer_width;
  GLint buffer_height;
};

#endif  // MY_WINDOW_H