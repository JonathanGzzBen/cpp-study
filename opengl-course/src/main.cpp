#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const float TO_RADIANS{3.14159265f / 180.0f};

using Program = struct {
  GLuint program;
  GLint uniformModel;
};

// Vector shader
const static std::string V_SHADER{R"(
    #version 330
    layout (location = 0) in vec3 pos;
    uniform mat4 model;
    void main() {
        gl_Position = model * vec4(pos, 1.0);
    }
)"};

//  Fragment shader
const static std::string F_SHADER{R"(
    #version 330
    out vec4 colour;
    void main() {
        colour = vec4(1.0, 0.0, 0.0, 1.0);
    }
)"};

void AddShader(GLuint theProgram, const std::string *shaderCode,
               GLenum shaderType) {
  GLuint theShader = glCreateShader(shaderType);
  std::array<GLint, 1> codeLength{(GLint)shaderCode->length()};
  auto theCode = shaderCode->data();
  glShaderSource(theShader, 1, &theCode, codeLength.data());
  glCompileShader(theShader);

  GLint result = 0;
  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (!result) {
    std::array<GLchar, 1024> eLog{};
    glGetShaderInfoLog(theShader, eLog.size(), nullptr, eLog.data());
    std::cerr << "Error compiling the " << shaderType << " shader: "
              << "'" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  glAttachShader(theProgram, theShader);
}

// Return shader program
Program CompileShadersProgram() {
  GLuint shader = glCreateProgram();
  if (!shader) {
    std::cerr << "Error creating shader program\n";
    exit(EXIT_FAILURE);
  }

  AddShader(shader, &V_SHADER, GL_VERTEX_SHADER);
  AddShader(shader, &F_SHADER, GL_FRAGMENT_SHADER);

  GLint result = 0;
  std::array<GLchar, 1024> eLog{};
  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog.data());
    std::cerr << "Error linking program: '" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog.data());
    std::cerr << "Error validating program: '" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  auto uniformModel = glGetUniformLocation(shader, "model");
  return {.program = shader, .uniformModel = uniformModel};
}

// Return VAO
GLuint CreateTriangle() {
  const std::array<float, 9> vertices{-1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
                                      0.0f,  0.0f,  1.0f, 0.0f};

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return vao;
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "GLFW initialization failed!\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Setup GLFW window properties
  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Core profile - No Backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *mainWindow =
      glfwCreateWindow(WIDTH, HEIGHT, "First GLFW window", nullptr, nullptr);
  if (!mainWindow) {
    std::cerr << "GLFW window creation failed\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Get Buffer size information
  int bufferWidth;
  int bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  // Set the context for GLFW to use
  glfwMakeContextCurrent(mainWindow);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW initialization failed\n";
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  GLuint vao = CreateTriangle();
  auto [program, uniformModel] = CompileShadersProgram();

  bool direction = true;
  float triOffset = 0.0f;
  float curAngle = 0.0f;
  float curSize = 0.4f;
  bool sizeDirection = true;
  // Loop until window closed
  while (!glfwWindowShouldClose(mainWindow)) {
    const float triMaxOffset = 0.6f;
    const float triIncrement = 0.005f;
    // Get and Handle user input events
    glfwPollEvents();

    triOffset += direction ? triIncrement : triIncrement * -1;

    if (std::fabs(triOffset) >= triMaxOffset) direction = !direction;

    curAngle = curAngle >= 360 ? curAngle - 360 : curAngle + 0.1f;

    const float maxSize = 0.8f;
    const float minSize = 0.1f;

    curSize = direction ? curSize + 0.001f : curSize - 0.001f;
    sizeDirection = (curSize < minSize || maxSize < curSize) ? !sizeDirection
                                                             : sizeDirection;

    // Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glm::mat4 model(1.0f);
    model =
        glm::rotate(model, curAngle * TO_RADIANS, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }

  exit(EXIT_SUCCESS);
}