#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H
#include <GL/glew.h>

#include "shader_object.h"

class ProgramObject {
 private:
  unsigned int reference;

 public:
  ProgramObject() {
    auto program = glCreateProgram();
    reference = program;
  }
  ~ProgramObject() = default;

  auto AttachShader(ShaderObject shader) const {
    glAttachShader(reference, shader.GetReference());
  }

  auto LinkProgram() const {
    glLinkProgram(reference);
    int link_status;
    glGetProgramiv(reference, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
      int log_length;
      glGetProgramiv(reference, GL_INFO_LOG_LENGTH, &log_length);
      std::string log;
      log.resize(log_length);
      glGetProgramInfoLog(reference, GL_INFO_LOG_LENGTH, &log_length,
                          log.data());
      std::cout << log;
      exit(EXIT_FAILURE);
    }
  }

  auto GetReference() const -> unsigned int { return reference; }
};

#endif  // PROGRAM_OBJECT_H