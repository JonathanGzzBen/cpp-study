#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#include <functional>

class Window {
 private:
  GLFWwindow* window;

 public:
  Window(const int width, const int height, const std::string& title) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
      glfwTerminate();
    }
  }
  ~Window() { glfwDestroyWindow(window); }

  auto MakeContextCurrent() const -> void { glfwMakeContextCurrent(window); }
  auto SetInputMode(const int mode, const int value) const -> void {
    glfwSetInputMode(window, mode, value);
  }
  auto SetFramebufferSizeCallback(GLFWframebuffersizefun callback) const
      -> void {
    glfwSetFramebufferSizeCallback(window, callback);
  }
  auto SetCursorPosCallback(GLFWcursorposfun callback) const -> void {
    glfwSetCursorPosCallback(window, callback);
  }
  auto SetScrollCallback(GLFWscrollfun callback) const -> void {
    glfwSetScrollCallback(window, callback);
  }
  auto GetShouldClose() const -> bool { return glfwWindowShouldClose(window); }
  auto SetShouldClose(bool value) const -> void {
    glfwSetWindowShouldClose(window, value);
  }
  auto GetKey(int key) const -> int { return glfwGetKey(window, key); }
  auto ProcessInput(const std::function<void(Window*)>& func) { func(this); }
  auto SwapBuffers() const -> void { glfwSwapBuffers(window); }
};

#endif  // WINDOW_H