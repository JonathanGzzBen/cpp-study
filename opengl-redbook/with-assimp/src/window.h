#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#include <functional>
#include <string>

#include "input_handler.h"

class Window {
 protected:
  GLFWwindow* window;
  InputHandler* input_handler;

 public:
  Window(const int width, const int height, const std::string& title) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
      glfwTerminate();
    }
    glfwSetWindowUserPointer(window, this);
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
  auto GetShouldClose() const -> bool { return glfwWindowShouldClose(window); }
  auto SetShouldClose(bool value) const -> void {
    glfwSetWindowShouldClose(window, value);
  }
  auto SetControls(InputHandler* controls) {
    this->input_handler = controls;
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetCursorPosCallback(window, controls->CursorPosCallback);
    glfwSetScrollCallback(window, controls->ScrollCallback);
    glfwSetKeyCallback(window, controls->KeyCallback);
  }
  auto GetControls() -> InputHandler* const { return input_handler; }
  auto Process(const std::function<void(Window*)>& func) { func(this); }
  auto SwapBuffers() const -> void { glfwSwapBuffers(window); }
};

#endif  // WINDOW_H