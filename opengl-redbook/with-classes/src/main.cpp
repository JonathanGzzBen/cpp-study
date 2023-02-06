#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "buffer_object.h"
#include "camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "input_handler.h"
#include "program_object.h"
#include "shader_object.h"
#include "texture.h"
#include "window.h"

using FigureBufferObjects = struct {
  BufferObject vbo;
  BufferObject ebo;
};

static auto GetSquaresBufferObjects() {
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

static auto SetTextures(const ProgramObject program) {
  stbi_set_flip_vertically_on_load(true);
  Texture textureNero(0, "textures/nero.jpg");
  glUniform1i(glGetUniformLocation(program.GetReference(), "image_texture"),
              static_cast<int>(textureNero.GetTextureUnitIndex()));
  Texture textureNino(1, "textures/nino.png");
  glUniform1i(glGetUniformLocation(program.GetReference(), "watermark_texture"),
              static_cast<int>(textureNino.GetTextureUnitIndex()));
}

static auto GetSquareVAO(const ProgramObject program) {
  /* Create VAO */
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* Bind VBO with vertex data and EBO with indices */
  auto squares_bo = GetSquaresBufferObjects();
  glBindBuffer(GL_ARRAY_BUFFER, squares_bo.vbo.GetBufferName());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squares_bo.ebo.GetBufferName());

  /* Attribs */
  const auto position_loc = program.GetAttribLocation("vPosition");
  const auto tex_coord_loc = program.GetAttribLocation("vTexCoord");
  const auto cube_position_loc = program.GetAttribLocation("vCubePosition");

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
  glViewport(0, 0, width, height);
}

static float last_frame = 0.0f;

static auto processInput(Window* window) {
  const auto input_handler = window->GetControls();
  if (input_handler->pressed[GLFW_KEY_ESCAPE]) window->SetShouldClose(true);
  float current_frame = (float)glfwGetTime();
  float delta_time = current_frame - last_frame;
  last_frame = current_frame;

  const float cameraSpeed = 2.5f * delta_time;
  const auto camera = window->GetControls()->GetCamera();
  if (input_handler->pressed[GLFW_KEY_W])
    camera->SetPosition(camera->GetPosition() +
                        (cameraSpeed * camera->GetFront()));
  if (input_handler->pressed[GLFW_KEY_S])
    camera->SetPosition(camera->GetPosition() -
                        (cameraSpeed * camera->GetFront()));
  if (input_handler->pressed[GLFW_KEY_A])
    camera->SetPosition(
        camera->GetPosition() -
        (glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) *
         cameraSpeed));
  if (input_handler->pressed[GLFW_KEY_D])
    camera->SetPosition(
        camera->GetPosition() +
        (glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) *
         cameraSpeed));
}

static int window_width = 700;
static int window_height = 700;
static auto ResizeViewport(GLFWwindow* window, int width, int height) {
  window_width = width;
  window_height = height;
  glViewport(0, 0, window_width, window_height);
}

int main() {
  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  Window window{window_width, window_height, CMAKE_PROJECT_NAME};

  /* Make the window's context current */
  window.MakeContextCurrent();
  window.SetFramebufferSizeCallback(ResizeViewport);
  std::cout << "Using version " << glfwGetVersionString() << "\n";

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit(EXIT_FAILURE);
  }

  ProgramObject program;
  program.AttachShader(
      ShaderObject(GL_VERTEX_SHADER, "shaders/triangles.vert"));
  program.AttachShader(
      ShaderObject(GL_FRAGMENT_SHADER, "shaders/triangles.frag"));
  program.LinkProgram();
  program.Use();
  SetTextures(program);
  const auto square_vao = GetSquareVAO(program);

  const auto model_matrix_location = program.GetUniformLocation("mModel");
  const auto view_matrix_location = program.GetUniformLocation("mView");
  const auto projection_matrix_location =
      program.GetUniformLocation("mProjection");

  const auto identity_matrix = glm::mat4(1.0f);

  constexpr auto instances_count = 9;

  glEnable(GL_DEPTH_TEST);
  window.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  Camera camera;
  InputHandler input_handler(&camera);
  window.SetControls(&input_handler);
  /* Loop until the user closes the window */
  while (!window.GetShouldClose()) {
    window.Process(processInput);
    /* Render here */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(square_vao);

    auto model_matrix = glm::mat4(1.0f);
    model_matrix = glm::scale(model_matrix, glm::vec3(0.15f, 0.15f, 0.15f));

    auto view_matrix =
        glm::lookAt(camera.GetPosition(),
                    camera.GetPosition() + camera.GetFront(), camera.GetUp());

    auto projection_matrix = glm::perspective(
        glm::radians(input_handler.fov),
        static_cast<float>(window_width) / static_cast<float>(window_height),
        0.1f, 100.0f);

    glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(model_matrix));
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(view_matrix));
    glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE,
                       glm::value_ptr(projection_matrix));

    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_INT, nullptr,
                            instances_count);

    /* Swap front and back VBOs */
    window.SwapBuffers();

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
