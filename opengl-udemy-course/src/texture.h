#ifndef TEXTURE_H
#define TEXTURE_H

// clang-format off
#include <gl/glew.h>
// clang-format on

#include "stb_image.h"

class Texture {
 public:
  Texture() = default;
  Texture(const char* file_location);
  ~Texture();

  void LoadTexture();
  void UseTexture();
  void ClearTexture();

 private:
  GLuint texture_id = 0;
  int width = 0;
  int height = 0;
  int bitDepth = 0;

  const char* file_location;
};

#endif  // TEXTURE_H