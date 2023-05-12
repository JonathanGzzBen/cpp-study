#include "my_window.h"

#include <iostream>

Window::Window() : width{800}, height{600} {
  for (size_t i = 0; i < 1024; i++) {
    keys[i] = 0;
  }
}

Window::Window(GLint window_width, GLint window_height)
    : width{window_width}, height{window_height} {
  for (size_t i = 0; i < 1024; i++) {
    keys[i] = 0;
  }
}

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

  // Handle Key + Mouse Input
  createCallbacks();
  glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

  glfwSetWindowUserPointer(main_window, this);
}

GLfloat Window::GetXChange() {
  GLfloat the_change = x_change;
  x_change = 0.0f;
  return the_change;
}

GLfloat Window::GetYChange() {
  GLfloat the_change = y_change;
  y_change = 0.0f;
  return the_change;
}

void Window::createCallbacks() {
  glfwSetKeyCallback(main_window, handleKeys);
  glfwSetCursorPosCallback(main_window, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action,
                        int mode) {
  Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      the_window->keys[key] = true;
    else if (action == GLFW_RELEASE)
      the_window->keys[key] = false;
  }
}

void Window::handleMouse(GLFWwindow* window, double x_pos, double y_pos) {
  Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (!the_window->mouse_first_moved) {
    the_window->last_x = x_pos;
    the_window->last_y = y_pos;
    the_window->mouse_first_moved = true;
  }

  the_window->x_change = x_pos - the_window->last_x;
  the_window->y_change = the_window->last_y - y_pos;

  the_window->last_x = x_pos;
  the_window->last_y = y_pos;
}
