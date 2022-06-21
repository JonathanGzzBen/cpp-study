#include "shader.h"

#include <array>
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader() : shaderId{0}, uniformProjection{0}, uniformModel{0} {}

Shader::~Shader() { ClearShader(); }

GLuint Shader::GetProjectionLocation() const { return uniformProjection; }

GLuint Shader::GetModelLocation() const { return uniformModel; }

void Shader::UseShader() const { glUseProgram(shaderId); }

void Shader::ClearShader() {
  if (shaderId != 0) {
    glDeleteProgram(shaderId);
    shaderId = 0;
  }
  uniformModel = 0;
  uniformProjection = 0;
}

void Shader::CreateFromString(const std::string* vertexCode,
                              const std::string* fragmentCode) {
  CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const std::string* vertexLocation,
        const std::string* fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    CompileShader(&vertexString, &fragmentString);
}

std::string Shader::ReadFile(const std::string* fileLocation) {
  std::string content;
  std::ifstream fileStream{*fileLocation, std::ios::in};

  if (!fileStream.is_open()) {
    std::cerr << "Failed to read " << fileLocation << "! File doesn't exist.\n";
    return "";
  }

  std::string line;
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content += line + "\n";
  }

  fileStream.close();
  return content;
}

void Shader::CompileShader(const std::string* vertexCode,
                           const std::string* fragmentCode) {
  shaderId = glCreateProgram();
  if (shaderId == 0U) {
    std::cerr << "Error creating shader program\n";
    exit(EXIT_FAILURE);
  }

  AddShader(shaderId, vertexCode, GL_VERTEX_SHADER);
  AddShader(shaderId, fragmentCode, GL_FRAGMENT_SHADER);

  GLint result = 0;
  std::array<GLchar, 1024> eLog{};
  glLinkProgram(shaderId);
  glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
  if (result == 0) {
    glGetProgramInfoLog(shaderId, sizeof(eLog), nullptr, eLog.data());
    std::cerr << "Error linking program: '" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  glValidateProgram(shaderId);
  glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
  if (result == 0) {
    glGetProgramInfoLog(shaderId, sizeof(eLog), nullptr, eLog.data());
    std::cerr << "Error validating program: '" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  uniformProjection = glGetUniformLocation(shaderId, "projection");
  uniformModel = glGetUniformLocation(shaderId, "model");
}

void Shader::AddShader(GLuint theProgram, const std::string* shaderCode,
                       GLenum shaderType) {
  GLuint theShader = glCreateShader(shaderType);
  std::array<GLint, 1> codeLength{(GLint)shaderCode->length()};
  const auto* theCode = shaderCode->data();
  glShaderSource(theShader, 1, &theCode, codeLength.data());
  glCompileShader(theShader);

  GLint result = 0;
  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (result == 0) {
    std::array<GLchar, 1024> eLog{};
    glGetShaderInfoLog(theShader, eLog.size(), nullptr, eLog.data());
    std::cerr << "Error compiling the " << shaderType << " shader: "
              << "'" << eLog.data() << "'\n";
    exit(EXIT_FAILURE);
  }

  glAttachShader(theProgram, theShader);
}
