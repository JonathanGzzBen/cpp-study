#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "window.h"

const float TO_RADIANS{3.14159265F / 180.0F};

std::vector<std::shared_ptr<Mesh>> meshList;
std::vector<std::shared_ptr<Shader>> shaderList;

// Vector shader
const static std::string V_SHADER{"shaders/shader.vert"};

//  Fragment shader
const static std::string F_SHADER{"shaders/shader.frag"};

// Return VAO
void CreateObjects() {
  std::array<unsigned int, 12> indices{0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};
  std::array<float, 12> vertices{-1.0F, -1.0F, 0.0F, 0.0F, -1.0F, 1.0F,
                                 1.0F,  -1.0F, 0.0F, 0.0F, 1.0F,  0.0F};

  auto obj1 = std::make_shared<Mesh>();
  obj1->CreateMesh(vertices.data(), indices.data(), 12, 12);
  meshList.push_back(obj1);

  auto obj2 = std::make_shared<Mesh>();
  obj2->CreateMesh(vertices.data(), indices.data(), 12, 12);
  meshList.push_back(obj2);
}

void CreateShaders() {
  auto shader = std::make_shared<Shader>();
  shader->CreateFromFiles(&V_SHADER, &F_SHADER);
  shaderList.push_back(shader);
}

int main() {
  // Window dimensions
  const GLint WIDTH = 800;
  const GLint HEIGHT = 600;
  Window mainWindow{WIDTH, HEIGHT};
  mainWindow.Initialize();

  CreateObjects();
  CreateShaders();

  GLint uniformProjection = 0;
  GLint uniformModel = 0;
  glm::mat4 projection =
      glm::perspective(45.0F,
                       static_cast<GLfloat>(mainWindow.getBufferWidth()) /
                           static_cast<GLfloat>(mainWindow.getBufferHeight()),
                       0.1F, 100.0F);

  // Loop until window closed
  while (mainWindow.getShouldClose() == 0) {
    // Get and Handle user input events
    glfwPollEvents();

    // Clear window
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderList[0]->UseShader();
    uniformModel = shaderList[0]->GetModelLocation();
    uniformProjection = shaderList[0]->GetProjectionLocation();

    glm::mat4 model(1.0F);
    model = glm::translate(model, glm::vec3(0.0F, 0.0F, -2.5F));
    model = glm::scale(model, glm::vec3(0.4F, 0.4F, 1.0F));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0F);
    model = glm::translate(model, glm::vec3(0.0F, 1.0F, -2.5F));
    model = glm::scale(model, glm::vec3(0.4F, 0.4F, 1.0F));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[1]->RenderMesh();

    glUseProgram(0);

    mainWindow.swapBuffers();
  }

  exit(EXIT_SUCCESS);
}
