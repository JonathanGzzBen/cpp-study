#include "window.h"
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window() : width{800}, height{600} {}

Window::Window(GLint windowWidth, GLint windowHeight)
    : width{windowWidth}, height{windowHeight} {}

Window::~Window() {
  glfwDestroyWindow(mainWindow);
  glfwTerminate();
}

int Window::Initialize() {
  // Initialize GLFW
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "GLFW initialization failed!\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Setup GLFW window properties
  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Core profile - No Backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mainWindow =
      glfwCreateWindow(width, height, "First GLFW window", nullptr, nullptr);
  if (mainWindow == nullptr) {
    std::cerr << "GLFW window creation failed\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Get Buffer size information
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  // Set the context for GLFW to use
  glfwMakeContextCurrent(mainWindow);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW initialization failed\n";
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glEnable(GL_DEPTH_TEST);

  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);
  return 0;
}
