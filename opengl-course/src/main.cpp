#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "window.h"

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const float TO_RADIANS{3.14159265f / 180.0f};

Window mainWindow;
std::vector<Mesh *> meshList;
std::vector<Shader *> shaderList;

// Vector shader
const static std::string V_SHADER{"shaders/shader.vert"};

//  Fragment shader
const static std::string F_SHADER{"shaders/shader.frag"};

// Return VAO
void CreateObjects() {
  std::array<unsigned int, 12> indices{0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};
  std::array<float, 12> vertices{-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f,
                                 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f};

  Mesh *obj1 = new Mesh();
  obj1->CreateMesh(vertices.data(), indices.data(), 12, 12);
  meshList.push_back(obj1);

  Mesh *obj2 = new Mesh();
  obj2->CreateMesh(vertices.data(), indices.data(), 12, 12);
  meshList.push_back(obj2);
}

void CreateShaders() {
  Shader *shader1 = new Shader();
  shader1->CreateFromFiles(&V_SHADER, &F_SHADER);
  shaderList.push_back(shader1);
}

int main() {
  mainWindow = Window(WIDTH, HEIGHT);
  mainWindow.Initialize();

  CreateObjects();
  CreateShaders();

  GLuint uniformProjection = 0;
  GLuint uniformModel = 0;
  glm::mat4 projection = glm::perspective(
      45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f,
      100.0f);

  bool direction = true;
  float triOffset = 0.0f;
  float curAngle = 0.0f;
  float curSize = 0.4f;
  bool sizeDirection = true;
  // Loop until window closed
  while (!mainWindow.getShouldClose()) {
    const float triMaxOffset = 0.6f;
    const float triIncrement = 0.005f;
    // Get and Handle user input events
    glfwPollEvents();

    triOffset += direction ? triIncrement : triIncrement * -1;

    if (std::fabs(triOffset) >= triMaxOffset) {
      direction = !direction;
    }

    curAngle = curAngle >= 360 ? curAngle - 360 : curAngle + 0.1f;

    const float maxSize = 0.8F;
    const float minSize = 0.1F;

    curSize = direction ? curSize + 0.001f : curSize - 0.001f;
    sizeDirection = (curSize < minSize || maxSize < curSize) == !sizeDirection;

    // Clear window
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderList[0]->UseShader();
    uniformModel = shaderList[0]->GetModelLocation();
    uniformProjection = shaderList[0]->GetProjectionLocation();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
    // model =
    // glm::rotate(model, curAngle * TO_RADIANS, glm::vec3(triOffset, 1.0f,
    // 0.0f));
    model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-triOffset, 1.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[1]->RenderMesh();

    glUseProgram(0);

    mainWindow.swapBuffers();
  }

  exit(EXIT_SUCCESS);
}
