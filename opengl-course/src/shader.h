#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>

#include <string>

class Shader {
 public:
  Shader();
  ~Shader();
  void CreateFromString(const std::string* vertexCode,
                        const std::string* fragmentCode);

  void CreateFromFiles(const std::string* vertexLocation,
                       const std::string* fragmentLocation);

  static std::string ReadFile(const std::string* fileLocation);

  GLint GetProjectionLocation() const;
  GLint GetModelLocation() const;
  void UseShader() const;
  void ClearShader();

 private:
  GLuint shaderId;
  GLint uniformProjection;
  GLint uniformModel;
  void CompileShader(const std::string* vertexCode,
                     const std::string* fragmentCode);
  static void AddShader(GLuint theProgram, const std::string* shaderCode,
                        GLenum shaderType);
};

#endif  // SHADER_H
