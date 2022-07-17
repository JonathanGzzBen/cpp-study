#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <malloc.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

int main() {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cerr << "Error!" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  {  // Scope to delete stack allocated VBOs and IBOs before calling
     // glfwTerminate()
    float positions[] = {
        -0.5f, -0.5f,  // 0
        0.5f,  -0.5f,  // 1
        0.5f,  0.5f,   // 2
        -0.5f, 0.5f    // 3
    };

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    IndexBuffer ibo(indices, 6);

    Shader shader{"res/shaders/Basic.shader"};

    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ibo.Unbind();

    float increment = 0.05f;
    float r = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
      /* Render here */
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      shader.Bind();
      shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

      va.Bind();
      //        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

      GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      if (r > 1.0f)
        increment = -0.05f;
      else if (r < 0.0f)
        increment = 0.05f;

      r += increment;

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }
  }
  glfwTerminate();
  return 0;
}
