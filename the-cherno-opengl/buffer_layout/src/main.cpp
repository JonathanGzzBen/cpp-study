#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <malloc.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "index_buffer.h"
#include "renderer.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

using ShaderProgramSource = struct {
  std::string VertexSource;
  std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath) {
  std::ifstream stream{filepath};
  std::string line;
  std::stringstream ss[2];
  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
  ShaderType type = ShaderType::NONE;
  while (std::getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }
  return {.VertexSource = ss[0].str(), .FragmentSource = ss[1].str()};
}

static unsigned int CompileShader(unsigned int type,
                                  const std::string &source) {
  GLCall(unsigned int id = glCreateShader(type));
  const char *src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

    char *message = (char *)alloca(length * sizeof(char));
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader!" << std::endl;
    std::cout << message << std::endl;
    GLCall(glDeleteShader(id));
    return 0;
  }

  return id;
}

static unsigned int CreateShader(const std::string &vertexShader,
                                 const std::string &fragmentShader) {
  GLCall(unsigned int program = glCreateProgram());
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));

  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

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

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
                                 nullptr));

    IndexBuffer ibo(indices, 6);

    auto source = ParseShader("res/shaders/Basic.shader");
    std::cout << "Vertex shader" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "Fragment shader" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader =
        CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    assert(location != -1);

    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    float increment = 0.05f;
    float r = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
      /* Render here */
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      GLCall(glUseProgram(shader));
      GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

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

    GLCall(glDeleteProgram(shader));
  }
  glfwTerminate();
  return 0;
}
