#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

// Window dimentions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW initialization failed!");
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

  GLFWwindow *mainWindow =
      glfwCreateWindow(WIDTH, HEIGHT, "First GLFW window", NULL, NULL);
  if (!mainWindow) {
    fprintf(stderr, "GLFW window creation failed");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Get Buffer size information
  int bufferWidth;
  int bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  // Set the context for GLFW to use
  glfwMakeContextCurrent(mainWindow);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "GLEW initialization failed");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  // Loop until window closed
  while (!glfwWindowShouldClose(mainWindow)) {
    // Get and Handle user input events
    glfwPollEvents();

    // Clear window
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(mainWindow);
  }

  exit(EXIT_SUCCESS);
}