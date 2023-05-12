#include "my_window.h"

#include <iostream>

Window::Window() : width{800}, height{600} {}

Window::Window(GLint window_width, GLint window_height)
    : width{window_width}, height{window_height} {}

Window::~Window() {
  glfwDestroyWindow(main_window);
  glfwTerminate();
}

int Window::Initialize() {
  if (!glfwInit()) {
    std::cerr << "GLFW Initialization failed" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Core profile = No Backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  main_window =
      glfwCreateWindow(width, height, "Udemy Course", nullptr, nullptr);
  if (!main_window) {
    std::cerr << "GLFW window creation failed" << std::endl;
    glfwTerminate();
    return 1;
  }

  // Get buffer size information
  glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

  // Set context for GLEW to use
  glfwMakeContextCurrent(main_window);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW initialization failed" << std::endl;
    glfwDestroyWindow(main_window);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST);

  // Set viewport size
  glViewport(0, 0, buffer_width, buffer_height);
}