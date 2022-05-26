#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// Vector shader
static const char *V_SHADER =
    "#version 330\n"
    "\n"
    "layout (location = 0) in vec3 pos;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\n";

// Fragment shader
static const char *F_SHADER =
    "#version 330\n"
    "\n"
    "out vec4 colour;\n"
    "\n"
    "void main() {\n"
    "    colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType) {
  GLuint theShader = glCreateShader(shaderType);
  const GLchar *theCode[1];
  theCode[0] = shaderCode;
  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);
  glShaderSource(theShader, 1, theCode, codeLength);
  glCompileShader(theShader);

  GLint result = 0;
  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (!result) {
    GLchar eLog[1024] = {0};
    glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
    fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
    exit(EXIT_FAILURE);
  }

  glAttachShader(theProgram, theShader);
}

// Return shader program
GLuint CompileShaders() {
  GLuint shader = glCreateProgram();
  if (!shader) {
    fprintf(stderr, "Error creating shader program");
    exit(EXIT_FAILURE);
  }

  AddShader(shader, V_SHADER, GL_VERTEX_SHADER);
  AddShader(shader, F_SHADER, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar eLog[1024] = {0};

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    fprintf(stderr, "Error linking program: '%s'\n", eLog);
    exit(EXIT_FAILURE);
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    fprintf(stderr, "Error validating program: '%s'\n", eLog);
    exit(EXIT_FAILURE);
  }
  return shader;
}

// Return VAO
GLuint CreateTriangle() {
  GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
                        0.0f,  0.0f,  1.0f, 0.0f};

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return vao;
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW initialization failed!");
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
      glfwCreateWindow(WIDTH, HEIGHT, "First GLFW window", NULL, NULL);
  if (!mainWindow) {
    fprintf(stderr, "GLFW window creation failed");
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
    fprintf(stderr, "GLEW initialization failed");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  GLuint vao = CreateTriangle();
  GLuint shader = CompileShaders();

  // Loop until window closed
  while (!glfwWindowShouldClose(mainWindow)) {
    // Get and Handle user input events
    glfwPollEvents();

    // Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }

  exit(EXIT_SUCCESS);
}