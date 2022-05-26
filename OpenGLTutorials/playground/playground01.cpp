#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main() {
  glewExperimental = true;
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  auto window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they "
                 "are not 3.3 compatible. Try the version 2.1.\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);  // Initialize GLEW
  glewExperimental = true;         // Needed in core profile
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    exit(EXIT_FAILURE);
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  exit(EXIT_SUCCESS);
}