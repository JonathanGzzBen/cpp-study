#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

class Window {
 public:
  Window();
  Window(GLint windowWidth, GLint windowHeight);
  ~Window();

  int Initialize();
  GLint getBufferWidth() const { return bufferWidth; }
  GLint getBufferHeight() const { return bufferHeight; }
  int getShouldClose() const { return glfwWindowShouldClose(mainWindow); }
  std::array<bool, 1024>* getKeys() { return &keys; }
  GLfloat getXChange();
  GLfloat getYChange();
  void swapBuffers() { glfwSwapBuffers(mainWindow); }

 private:
  GLFWwindow* mainWindow{nullptr};
  GLint width;
  GLint height;
  GLint bufferWidth{0};
  GLint bufferHeight{0};
  std::array<bool, 1024> keys;

  GLfloat lastX;
  GLfloat lastY;
  GLfloat xChange{0};
  GLfloat yChange{0};
  bool mouseFirstMove;

  void createCallbacks();
  static void handleKeys(GLFWwindow* window, int key, int code, int action,
                         int mode);
  static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
#endif  // WINDOW_H
