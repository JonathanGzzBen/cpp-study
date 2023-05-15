#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "camera.h"
#include "mesh.h"
#include "my_window.h"
#include "shader.h"
#include "texture.h"

Window main_window;
std::vector<Mesh*> mesh_list;
std::vector<Shader> shader_list;
Camera camera;

Texture brick_texture;
Texture dirt_texture;

GLfloat delta_time = 0.0f;
GLfloat last_time = 0.0f;

// Vertex Shader
static const char* vShader = "shaders/shader.vert";

// Fragment shader
static const char* fShader = "shaders/shader.frag";

void CreateObjects() {
  unsigned int indices[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};
  // clang-format off
  GLfloat vertices[] = {
  // x      y      z      u
    -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,
     0.0f, -1.0f,  1.0f, 0.5f, 0.0f,
     1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  1.0f,  0.0f, 0.5f, 1.0f};
  // clang-format on

  Mesh* obj1 = new Mesh();
  obj1->CreateMesh(vertices, indices, 20, 12);
  mesh_list.push_back(obj1);

  Mesh* obj2 = new Mesh();
  obj2->CreateMesh(vertices, indices, 20, 12);
  mesh_list.push_back(obj2);
}

void AddShader(GLuint the_program, const char* shader_code,
               GLenum shader_type) {
  GLuint the_shader = glCreateShader(shader_type);
  const GLchar* the_code[1];
  the_code[0] = shader_code;

  GLint code_length[1];
  code_length[0] = static_cast<GLint>(strlen(shader_code));

  glShaderSource(the_shader, 1, the_code, code_length);
  glCompileShader(the_shader);

  GLint result = 0;
  GLchar error_log[1024] = {0};

  glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(the_shader, sizeof(error_log), nullptr, error_log);
    std::cerr << "Error compiling the " << shader_type << " shader: \""
              << error_log << "\"" << std::endl;
    return;
  }

  glAttachShader(the_program, the_shader);
}

void CreateShaders() {
  Shader* shader1 = new Shader();
  shader1->CreateFromFiles(vShader, fShader);
  shader_list.push_back(*shader1);
}

int main() {
  main_window = Window();
  main_window.Initialize();

  CreateObjects();
  CreateShaders();
  camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                  -90.0f, 0.0f, 5.0f, 0.5f);

  brick_texture = Texture("textures/brick.png");
  brick_texture.LoadTexture();
  dirt_texture = Texture("textures/dirt.png");
  dirt_texture.LoadTexture();

  GLuint uniform_projection = 0;
  GLuint uniform_model = 0;
  GLuint uniform_view = 0;
  glm::mat4 projection =
      glm::perspective(45.0f,
                       static_cast<GLfloat>(main_window.GetBufferWidth()) /
                           static_cast<GLfloat>(main_window.GetBufferHeight()),
                       0.1f, 100.0f);

  // Loop until window closed
  while (!main_window.GetShouldClose()) {
    GLfloat now = glfwGetTime();
    delta_time = now - last_time;
    last_time = now;

    // Get and handle user input events
    glfwPollEvents();

    camera.KeyControl(main_window.GetKeys(), delta_time);
    camera.MouseControl(main_window.GetXChange(), main_window.GetYChange());

    // Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_list[0].UseShader();
    uniform_model = shader_list[0].GetModelLocation();
    uniform_projection = shader_list[0].GetProjectionLocation();
    uniform_view = shader_list[0].GetViewLocation();

    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniform_projection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    glUniformMatrix4fv(uniform_view, 1, GL_FALSE,
                       glm::value_ptr(camera.CalculateViewMatrix()));
    brick_texture.UseTexture();
    mesh_list[0]->RenderMesh();

    model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniform_projection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    dirt_texture.UseTexture();
    mesh_list[1]->RenderMesh();

    glUseProgram(0);

    main_window.SwapBuffers();
  }

  return 0;
}