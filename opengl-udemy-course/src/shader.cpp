#include "shader.h"

#include <fstream>
#include <iostream>

Shader::~Shader() { ClearShader(); }

void Shader::CreateFromString(const char* vertex_code,
                              const char* fragment_code) {
  CompileShader(vertex_code, fragment_code);
}

void Shader::CreateFromFiles(const char* vertex_location,
                             const char* fragment_location) {
  std::string vertex_code = ReadFile(vertex_location);
  std::string fragment_code = ReadFile(fragment_location);

  CreateFromString(vertex_code.c_str(), fragment_code.c_str());
}

GLuint Shader::GetProjectionLocation() const { return uniform_projection; }

GLuint Shader::GetModelLocation() const { return uniform_model; }

GLuint Shader::GetViewLocation() const {return uniform_view;}

void Shader::UseShader() { glUseProgram(shader_id); }

void Shader::ClearShader() {
  if (shader_id != 0) {
    glDeleteProgram(shader_id);
    shader_id = 0;
  }
  uniform_model = 0;
  uniform_projection = 0;
  uniform_view = 0;
}

std::string Shader::ReadFile(const char* file_location) const {
  std::string content;
  std::ifstream file_stream(file_location, std::ios::in);
  if (!file_stream.is_open()) {
    std::cerr << "Failed to read \"" << file_location
              << "\". File doesn't exist." << std::endl;
    return "";
  }
  std::string line;
  while (!file_stream.eof()) {
    std::getline(file_stream, line);
    content.append(line + '\n');
  }
  file_stream.close();
  return content;
}

void Shader::CompileShader(const char* vertex_code, const char* fragment_code) {
  shader_id = glCreateProgram();
  if (!shader_id) {
    std::cerr << "Error creating shader program" << std::endl;
    return;
  }

  AddShader(shader_id, vertex_code, GL_VERTEX_SHADER);
  AddShader(shader_id, fragment_code, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar error_log[1024];

  glLinkProgram(shader_id);
  glGetProgramiv(shader_id, GL_LINK_STATUS, &result);

  if (!result) {
    glGetProgramInfoLog(shader_id, sizeof(error_log), nullptr, error_log);
    std::cerr << "Error linking program: \"" << error_log << "\"" << std::endl;
    return;
  }

  glValidateProgram(shader_id);
  glGetProgramiv(shader_id, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader_id, sizeof(error_log), nullptr, error_log);
    std::cerr << "Error validating program: \"" << error_log << "\""
              << std::endl;
    return;
  }

  uniform_model = glGetUniformLocation(shader_id, "model");
  uniform_projection = glGetUniformLocation(shader_id, "projection");
  uniform_view = glGetUniformLocation(shader_id, "view");
}

void Shader::AddShader(GLuint the_program, const char* shader_code,
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
