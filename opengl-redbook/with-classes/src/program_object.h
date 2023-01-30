#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H
#include <GL/glew.h>

#include "shader_object.h"

class ProgramObject {
 private:
  unsigned int program;

 public:
  ProgramObject() { program = glCreateProgram(); }
  ~ProgramObject() = default;

  auto AttachShader(const ShaderObject shader) const -> void {
    glAttachShader(program, shader.GetReference());
  }

  auto LinkProgram() const {
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
  }

  auto GetReference() const -> unsigned int { return program; }
  auto Use() const -> void { glUseProgram(program); }

  auto GetUniformLocation(const std::string& name) const -> int {
    return glGetUniformLocation(program, name.c_str());
  }
  auto GetAttribLocation(const std::string& name) const -> int {
    return glGetAttribLocation(program, name.c_str());
  }
};

#endif  // PROGRAM_OBJECT_H