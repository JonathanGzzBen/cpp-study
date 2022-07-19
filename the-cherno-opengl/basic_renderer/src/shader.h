#ifndef SHADER_ABSTRACTION_SHADER_H
#define SHADER_ABSTRACTION_SHADER_H

#include <string>
#include <unordered_map>

using ShaderProgramSource = struct {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
 private:
  std::string m_FilePath;
  unsigned int m_RendererID;
  // caching for uniforms
  std::unordered_map<std::string, unsigned int> m_UniformLocationCache;

 public:
  explicit Shader(const std::string& filepath);
  virtual ~Shader();

  void Bind() const;
  void Unbind() const;

  // Set uniforms
  void SetUniform4f(const std::string& name, float v0, float v1, float v2,
                    float v3);

 private:
  ShaderProgramSource ParseShader(const std::string& filepath);
  unsigned int CreateShader(const std::string& vertexShader,
                            const std::string& fragmentShader);
  unsigned int CompileShader(unsigned int type, const std::string& source);

  unsigned int GetUniformLocation(const std::string& name);
};

#endif  // SHADER_ABSTRACTION_SHADER_H
