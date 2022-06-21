#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
 public:
  Window();
  Window(GLint windowWidth, GLint windowHeight);
  ~Window();

  int Initialize();
  GLint getBufferWidth() const { return bufferWidth; }
  GLint getBufferHeight() const { return bufferHeight; }
  int getShouldClose() const { return glfwWindowShouldClose(mainWindow); }
  void swapBuffers() { glfwSwapBuffers(mainWindow); }

 private:
  GLFWwindow *mainWindow{nullptr};
  GLint width;
  GLint height;
  GLint bufferWidth{0};
  GLint bufferHeight{0};
};
#endif  // WINDOW_H
