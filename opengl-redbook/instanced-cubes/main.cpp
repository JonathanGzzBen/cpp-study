#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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

static auto CompileProgram(const std::string& vertex_shader_filename,
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
      // Front face
      // positions        // texture coords
      -0.5f, 0.5f, 0.5f, 0.0, 1.0f,     // 0 front top left
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     // 1 front top right
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // 2 front bottom left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // 3 front bottom right
      -0.5f, 0.5f, -0.5f, 0.0, 1.0f,    // 4 back top left
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // 5 back top right
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 6 back bottom left
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   // 7 back bottom right

      // Center cube
      0.0f, 0.0f, 0.0f,  // offset

      // Right cubes
      1.0f, 1.0f, 1.0f,    // offset
      1.0f, 1.0f, -1.0f,   // offset
      1.0f, -1.0f, 1.0f,   // offset
      1.0f, -1.0f, -1.0f,  // offset

      // Left cubes
      -1.0f, 1.0f, 1.0f,    // offset
      -1.0f, 1.0f, -1.0f,   // offset
      -1.0f, -1.0f, 1.0f,   // offset
      -1.0f, -1.0f, -1.0f,  // offset
  };
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

  unsigned int ebo;
  glCreateBuffers(1, &ebo);
  /* Set up element array buffer */
  if (!glIsEnabled(GL_PRIMITIVE_RESTART)) {
    glEnable(GL_PRIMITIVE_RESTART);
  }
  glPrimitiveRestartIndex(0xFFFF);
  const unsigned int indices[] = {
      4,      5, 0, 1, 2, 3, 6, 7,  // First strip
      0xFFFF,                       // Restart
      0,      2, 4, 6, 5, 7, 1, 3,  // Second strip
  };
  glNamedBufferStorage(ebo, sizeof(indices), indices, 0);
  return FigureBufferObjects{.vbo = vbo, .ebo = ebo};
}

static auto GetAndBindTexture(const std::string& filename) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width;
  int height;
  int channels;
  const auto data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
  if (!data) {
    std::cerr << "Could not load texture file " << filename << "\n";
    exit(EXIT_FAILURE);
  }
  if (width % 4 != 0) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  return texture;
}

static auto BindImageToTexture2D(unsigned int program,
                                 const std::string& filename,
                                 unsigned int texture_unit_index,
                                 const std::string& texture_uniform_name) {
  glActiveTexture(GL_TEXTURE0 + texture_unit_index);
  GetAndBindTexture(filename);
  glUniform1i(glGetUniformLocation(program, texture_uniform_name.c_str()),
              static_cast<int>(texture_unit_index));
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

  stbi_set_flip_vertically_on_load(true);
  BindImageToTexture2D(program, "textures/nero.jpg", 0, "image_texture");
  BindImageToTexture2D(program, "textures/nino.png", 1, "watermark_texture");

  /* Attribs */
  unsigned int position_loc = glGetAttribLocation(program, "vPosition");
  unsigned int tex_coord_loc = glGetAttribLocation(program, "vTexCoord");
  unsigned int cube_position_loc =
      glGetAttribLocation(program, "vCubePosition");

  glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        nullptr);

  glVertexAttribPointer(tex_coord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        (void*)(sizeof(float) * 3));

  glVertexAttribPointer(cube_position_loc, 3, GL_FLOAT, GL_FALSE, 0,
                        (void*)(sizeof(float) * 40));

  glEnableVertexAttribArray(position_loc);
  glEnableVertexAttribArray(tex_coord_loc);
  glEnableVertexAttribArray(cube_position_loc);
  glVertexAttribDivisor(cube_position_loc, 1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return vao;
}

static auto framebuffer_size_callback(GLFWwindow* window, int width,
                                      int height) {
  int frame_side_size = (width < height) ? width : height;
  glViewport(0, 0, frame_side_size, frame_side_size);
}

static auto processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window =
      glfwCreateWindow(700, 700, CMAKE_PROJECT_NAME, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  std::cout << "Using version " << glfwGetVersionString() << "\n";

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

  const auto model_matrix_location = glGetUniformLocation(program, "mModel");
  const auto view_matrix_location = glGetUniformLocation(program, "mView");
  const auto projection_matrix_location =
      glGetUniformLocation(program, "mProjection");

  const auto cube_positions_location =
      glGetUniformLocation(program, "vCubePositions");

  const auto identity_matrix = glm::mat4(1.0f);
  glm::mat4 cube_positions[] = {
      glm::translate(identity_matrix, glm::vec3(0.0f, 0.0f, 0.0f)),
      glm::translate(identity_matrix, glm::vec3(0.2f, 0.2f, 0.2f)),
  };

  constexpr auto instances_count = 9;

  glEnable(GL_DEPTH_TEST);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    /* Render here */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(square_vao);

    auto model_matrix = glm::mat4(1.0f);
    model_matrix =
        glm::rotate(model_matrix, (float)glfwGetTime() * glm::radians(50.0f),
                    glm::vec3(0.5f, 0.5f, 0.0f));
    model_matrix = glm::scale(model_matrix, glm::vec3(0.15f, 0.15f, 0.15f));

    auto view_matrix = glm::mat4(1.0f);
    view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -0.8f));
    auto projection_matrix = glm::mat4(1.0f);
    projection_matrix =
        glm::perspective(glm::radians(45.0f), 700.0f / 700.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(model_matrix));
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(view_matrix));
    glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(projection_matrix));

    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_INT, nullptr,
                            instances_count);

    /* Swap front and back VBOs */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
