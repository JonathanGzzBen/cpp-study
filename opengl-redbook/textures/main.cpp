#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stbi_image.h"

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
      // positions          // colors                      // texture coords
      -0.9f, 0.9f,  1.0f, 0.0f, 0.0f, 0.0,  0.0f,  // top left
      0.9f,  0.9f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // top right
      -0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
      0.9f,  -0.9f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f   // bottom right
  };
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

  unsigned int ebo;
  glCreateBuffers(1, &ebo);
  /* Set up element array buffer */
  const unsigned int indices[] = {0, 1, 2, 3};
  glNamedBufferStorage(ebo, sizeof(indices), indices, 0);
  return FigureBufferObjects{.vbo = vbo, .ebo = ebo};
}

static auto GetTexture(const std::string& filename) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width;
  int height;
  int channels;
  const auto data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
  if (!data) {
    std::cerr << "Could not load texture file " << filename << "\n";
    exit(EXIT_FAILURE);
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}

static auto GetSquareVAO(const unsigned int program) {
  /* Create VAO */
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* Bind VBO with vertex data and EBO with indices */
  auto square_bo = GetSquareBufferObjects();
  glBindBuffer(GL_ARRAY_BUFFER, square_bo.vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square_bo.ebo);
  glBindTexture(GL_TEXTURE_2D, GetTexture("textures/nino-profile.jpg"));

  /* Attribs */
  unsigned int position_loc = glGetAttribLocation(program, "vPosition");
  unsigned int color_loc = glGetAttribLocation(program, "vColor");
  unsigned int tex_coord_loc = glGetAttribLocation(program, "vTexCoord");

  glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7,
                        nullptr);
  glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7,
                        (void*)(sizeof(float) * 2));

  glVertexAttribPointer(color_loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7,
                        (void*)(sizeof(float) * 5));

  glEnableVertexAttribArray(position_loc);
  glEnableVertexAttribArray(color_loc);

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

  const unsigned int square_vao = GetSquareVAO(program);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(square_vao);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back VBOs */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
