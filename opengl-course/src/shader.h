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

  std::string ReadFile(const std::string* fileLocation);

  GLuint GetProjectionLocation();
  GLuint GetModelLocation();
  void UseShader();
  void ClearShader();

 private:
  GLuint shaderId;
  GLuint uniformProjection;
  GLuint uniformModel;
  void CompileShader(const std::string* vertexCode,
                     const std::string* fragmentCode);
  void AddShader(GLuint theProgram, const std::string* shaderCode,
                 GLenum shaderType);
};

#endif  // SHADER_H
