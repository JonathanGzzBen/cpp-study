#include "window.h"

#include <GLFW/glfw3.h>

#include <iostream>

Window::Window() : width{800}, height{600} {
  for (size_t i = 0; i < 1024; i++) {
    keys[i] = false;
  }
}

Window::Window(GLint windowWidth, GLint windowHeight)
    : width{windowWidth}, height{windowHeight} {
  for (size_t i = 0; i < 1024; i++) {
    keys[i] = false;
  }
}

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

  // Handle Key + Mouse Input
  createCallbacks();
  glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

  glfwSetWindowUserPointer(mainWindow, this);
  return 0;
}

GLfloat Window::getXChange() {
  GLfloat theChange = xChange;
  xChange = 0.0f;
  return theChange;
}

GLfloat Window::getYChange() {
  GLfloat theChange = yChange;
  yChange = 0.0f;
  return theChange;
}

void Window::createCallbacks() {
  glfwSetKeyCallback(mainWindow, Window::handleKeys);
  glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action,
                        int mode) {
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  } else if (0 <= key && key < 1024) {
    if (action == GLFW_PRESS) {
      theWindow->keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      theWindow->keys[key] = false;
    }
  }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (theWindow->mouseFirstMove) {
    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
    theWindow->mouseFirstMove = false;
  }

  theWindow->xChange = xPos - theWindow->lastX;
  theWindow->yChange = theWindow->lastY - yPos;

  theWindow->lastX = xPos;
  theWindow->lastY = yPos;
}
