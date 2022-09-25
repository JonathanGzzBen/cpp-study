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

  const auto vertex_shader =
      LoadShader(GL_VERTEX_SHADER, "shaders/triangles.vert");

  const auto fragment_shader =
      LoadShader(GL_FRAGMENT_SHADER, "shaders/triangles.frag");

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

  /* Create and populate VBOs */
  const int num_vertices = 6;
  const float vertices[num_vertices][2] = {{-0.90f, -0.90f}, {0.85f, -0.90f},
                                           {-0.90f, 0.85f},  {0.90f, -0.85f},
                                           {0.90f, 0.90f},   {-0.85f, 0.90f}};

  const unsigned int vertices_vbo = 0;
  const unsigned int number_of_vbos = 1;
  unsigned int VBOs[number_of_vbos];
  glCreateBuffers(number_of_vbos, VBOs);
  glNamedBufferStorage(VBOs[vertices_vbo], sizeof(vertices), vertices, 0);

  glUseProgram(program);
  const unsigned int triangles_vao = 0;
  const unsigned int number_of_vaos = 1;
  unsigned int VAOs[number_of_vaos];
  glGenVertexArrays(number_of_vaos, VAOs);
  glBindVertexArray(VAOs[triangles_vao]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[vertices_vbo]);
  unsigned int vPosition = 0;
  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexArrayAttrib(VAOs[triangles_vao], vPosition);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT);
    static const float black[] = {1.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOs[triangles_vao]);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    /* Swap front and back VBOs */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
