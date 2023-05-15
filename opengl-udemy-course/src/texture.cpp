#include "texture.h"

#include <iostream>

Texture::Texture(const char* file_location) : file_location{file_location} {}

Texture::~Texture() { ClearTexture(); }

void Texture::LoadTexture() {
  unsigned char* texture_data =
      stbi_load(file_location, &width, &height, &bitDepth, 0);
  if (!texture_data) {
    std::cerr << "Failed to find " << file_location << std::endl;
    return;
  }

  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, texture_data);

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(texture_data);
}

void Texture::UseTexture() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::ClearTexture() {
  glDeleteTextures(1, &texture_id);
  texture_id = 0;
  width = 0;
  height = 0;
  bitDepth = 0;
  file_location = "";
}
