#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "buffer_object.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "program_object.h"
#include "shader_object.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "texture.h"

static auto CompileProgram(const std::string& vertex_shader_filename,
                           const std::string& fragment_shader_filename) {
  const auto vertex_shader =
      ShaderObject(GL_VERTEX_SHADER, vertex_shader_filename);

  const auto fragment_shader =
      ShaderObject(GL_FRAGMENT_SHADER, fragment_shader_filename);

  /* Create program */
  ProgramObject program;
  program.AttachShader(vertex_shader);
  program.AttachShader(fragment_shader);
  program.LinkProgram();
  return program.GetReference();
}

using FigureBufferObjects = struct {
  BufferObject vbo;
  BufferObject ebo;
};

static auto GetSquareBufferObjects() {
  /* Store vertices in a vertex buffer object */
  const float vertices[] = {
      // Front face
      // positions       // texture coords
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 0 front top left
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // 1 front top right
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // 2 front bottom left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // 3 front bottom right
      // Back face
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // 4 back top left
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
  BufferObject vbo((void*)vertices, sizeof(vertices));

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
  BufferObject ebo((void*)indices, sizeof(indices));

  return FigureBufferObjects{.vbo = vbo, .ebo = ebo};
}

static auto BindImageToTexture2D(unsigned int program,
                                 const std::string& filename,
                                 unsigned int texture_unit_index,
                                 const std::string& texture_uniform_name) {
  glActiveTexture(GL_TEXTURE0 + texture_unit_index);
  Texture texture(filename);
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
  glBindBuffer(GL_ARRAY_BUFFER, square_bo.vbo.GetBufferName());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square_bo.ebo.GetBufferName());

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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

static auto processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  float currentFrame = (float)glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  const float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

bool firstMouse = true;
float lastX = 350;
float lastY = 350;
float yaw = -90.0f;
float pitch = 0.0f;
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
  if (firstMouse) {
    lastX = static_cast<float>(xPos);
    lastY = static_cast<float>(yPos);
    firstMouse = false;
  }

  float xOffset = static_cast<float>(xPos) - lastX;
  float yOffset = lastY - static_cast<float>(yPos);
  lastX = static_cast<float>(xPos);
  lastY = static_cast<float>(yPos);

  float sensitivity = 0.1f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;

  pitch = (pitch > 89.0f) ? 89.0f : pitch;
  pitch = (pitch < -89.0f) ? -89.0f : pitch;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}

float fov = 45.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  fov -= (float)yoffset;
  if (fov < 1.0f) fov = 1.0f;
  if (fov > 45.0f) fov = 45.0f;
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

  const auto identity_matrix = glm::mat4(1.0f);

  constexpr auto instances_count = 9;

  glEnable(GL_DEPTH_TEST);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    /* Render here */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(square_vao);

    auto model_matrix = glm::mat4(1.0f);
    model_matrix = glm::scale(model_matrix, glm::vec3(0.15f, 0.15f, 0.15f));

    constexpr float radius = 1.0f;
    const auto camX = sin(glfwGetTime()) * radius;
    const auto camZ = cos(glfwGetTime()) * radius;
    auto view_matrix = glm::mat4(1.0f);
    view_matrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    auto projection_matrix = glm::mat4(1.0f);
    projection_matrix =
        glm::perspective(glm::radians(fov), 700.0f / 700.0f, 0.1f, 100.0f);

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
