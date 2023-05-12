#ifndef SHADER_H
#define SHADER_H
#include <gl/glew.h>

#include <string>

class Shader {
 public:
  Shader() = default;
  ~Shader();

  void CreateFromString(const char* vertex_code, const char* fragment_code);
  void CreateFromFiles(const char* vertex_location,
                       const char* fragment_location);

  GLuint GetProjectionLocation() const;
  GLuint GetModelLocation() const;
  GLuint GetViewLocation() const;
  void UseShader();
  void ClearShader();

 private:
  GLuint shader_id = 0;
  GLuint uniform_projection = 0;
  GLuint uniform_model = 0;
  GLuint uniform_view = 0;

  std::string ReadFile(const char* file_location) const;

  void CompileShader(const char* vertex_code, const char* fragment_code);
  void AddShader(GLuint the_program, const char* shader_code,
                 GLenum shader_type);
};

#endif  // SHADER_H