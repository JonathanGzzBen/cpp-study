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
  GLfloat getBufferWidth() const { return bufferWidth; }
  GLfloat getBufferHeight() const { return bufferHeight; }
  int getShouldClose() const { return glfwWindowShouldClose(mainWindow); }
  void swapBuffers() { glfwSwapBuffers(mainWindow); }

 private:
  GLFWwindow *mainWindow;
  GLint width;
  GLint height;
  GLint bufferWidth;
  GLint bufferHeight;
};
#endif  // WINDOW_H
