#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stbi_image.h"

class Texture {
 private:
  unsigned int texture_unit_index;
  unsigned int texture_name;

 public:
  /// @brief Creates and binds texture
  /// @param filename
  Texture(const unsigned int texture_unit_index, const std::string& filename)
      : texture_unit_index{texture_unit_index} {
    glActiveTexture(GL_TEXTURE0 + texture_unit_index);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width;
    int height;
    int channels;
    const auto data =
        stbi_load(filename.c_str(), &width, &height, &channels, 4);
    if (!data) {
      std::cerr << "Could not load texture file " << filename << "\n";
      exit(EXIT_FAILURE);
    }
    if (width % 4 != 0) {
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    texture_name = texture;
  }
  ~Texture() = default;

  auto GetTextureName() const -> unsigned int { return texture_name; }
  auto GetTextureUnitIndex() const -> unsigned int {
    return texture_unit_index;
  }
};

#endif  // TEXTURE_H