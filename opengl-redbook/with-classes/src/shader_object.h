#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>

class ShaderObject {
 private:
  unsigned int type;
  unsigned int reference;

  std::string load_source_file(const std::string& filename) {
    std::ifstream input_file{filename};
    if (!input_file.is_open()) {
      std::cerr << "Error opening file " << filename << "\n";
      exit(EXIT_FAILURE);
    }

    std::string file_content;
    while (input_file.good()) {
      std::string buf;
      std::getline(input_file, buf);
      file_content += buf + "\n";
    }

    return file_content;
  }

 public:
  ShaderObject(unsigned int type, const std::string& filename) : type{type} {
    const auto shader = glCreateShader(type);
    std::string shader_source_str{load_source_file(filename)};

    const char* shader_src = shader_source_str.c_str();
    glShaderSource(shader, 1, &shader_src, nullptr);
    glCompileShader(shader);
    int compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
      int log_length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
      std::string log;
      log.resize(log_length);
      glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, &log_length, log.data());
      std::cout << log;
      exit(EXIT_FAILURE);
    }
    reference = shader;
  }
  ~ShaderObject() = default;

  auto GetReference() const -> unsigned int { return reference; }
  auto GetType() const -> unsigned int { return type; }
};

#endif  // SHADER_OBJECT_H