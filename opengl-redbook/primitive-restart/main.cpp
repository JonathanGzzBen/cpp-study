#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

std::string load_source_file(const std::string& filename) {
  std::ifstream input_file{filename};
  if (!input_file.is_open()) {
    std::cerr << "Error opening file " << filename << "\n";
    exit(EXIT_FAILURE);
  }

  std::string file_content;
  while (input_file.good()) {
    std::string buf;
    std::getline(input_file, buf);
    file_content += buf + "\n";
  }

  return file_content;
}

static unsigned int LoadShader(unsigned int type, const std::string& filename) {
  /* Create shader */
  const auto shader = glCreateShader(type);
  std::string shader_source_str{load_source_file(filename)};

  const char* shader_src = shader_source_str.c_str();
  glShaderSource(shader, 1, &shader_src, nullptr);
  glCompileShader(shader);
  int compile_status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    int log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    std::string log;
    log.resize(log_length);
    glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, &log_length, log.data());
    std::cout << log;
    exit(EXIT_FAILURE);
  }
  return shader;
}

unsigned int CompileProgram(const std::string& vertex_shader_filename,
                            const std::string& fragment_shader_filename) {
  const auto vertex_shader =
      LoadShader(GL_VERTEX_SHADER, vertex_shader_filename);

  const auto fragment_shader =
      LoadShader(GL_FRAGMENT_SHADER, fragment_shader_filename);

  /* Create program */
  auto program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  int link_status;
  glGetProgramiv(program, GL_LINK_STATUS, &link_status);
  if (link_status != GL_TRUE) {
    int log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    std::string log;
    log.resize(log_length);
    glGetProgramInfoLog(program, GL_INFO_LOG_LENGTH, &log_length, log.data());
    std::cout << log;
    exit(EXIT_FAILURE);
  }
  return program;
}

using FigureBufferObjects = struct {
  unsigned int vbo;
  unsigned int ebo;
};

static auto GetSquareBufferObjects() {
  unsigned int vbo;
  glCreateBuffers(1, &vbo);
  /* Store vertices in a vertex buffer object */
  const float vertices[] = {
      -0.9f, 0.9f,   // top left
      0.9f,  0.9f,   // top right
      -0.9f, -0.9f,  // bottom left
      0.9f,  -0.9f   // bottom right
  };
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

  unsigned int ebo;
  glCreateBuffers(1, &ebo);
  /* Set up element array buffer */
  const unsigned int indices[] = {
      0,      1, 2,  // top left triangle
      0xFFFF,        // restart index
      1,      2, 3   // bottom right triangle
  };
  glNamedBufferStorage(ebo, sizeof(indices), indices, 0);
  return FigureBufferObjects{.vbo = vbo, .ebo = ebo};
}

static auto GetSquareVAO() {
  /* Create VAO */
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* Bind VBO with vertex data and EBO with indices */
  auto square_bo = GetSquareBufferObjects();
  glBindBuffer(GL_ARRAY_BUFFER, square_bo.vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square_bo.ebo);

  /* Attribs */
  unsigned int position = 0;
  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(position);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return vao;
}

int main() {
  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window =
      glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit(EXIT_FAILURE);
  }

  const auto program =
      CompileProgram("shaders/triangles.vert", "shaders/triangles.frag");

  /* Use program */
  glUseProgram(program);

  const unsigned int square_vao = GetSquareVAO();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(square_vao);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back VBOs */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
