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
  bool* GetKeys() { return keys; }
  GLfloat GetXChange();
  GLfloat GetYChange();
  void SwapBuffers() const { glfwSwapBuffers(main_window); }

 private:
  GLFWwindow* main_window = nullptr;
  GLint width;
  GLint height;
  GLint buffer_width;
  GLint buffer_height;

  GLfloat last_x;
  GLfloat last_y;
  GLfloat x_change = 0.0f;
  GLfloat y_change = 0.0f;
  bool mouse_first_moved = false;

  bool keys[1024];
  void createCallbacks();
  static void handleKeys(GLFWwindow* window, int key, int code, int action,
                         int mode);
  static void handleMouse(GLFWwindow* window, double x_pos, double y_pos);
};

#endif  // MY_WINDOW_H