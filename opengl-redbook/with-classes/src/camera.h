#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#include "glm/glm.hpp"

class Camera {
 private:
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

 public:
  Camera() {}
  ~Camera() = default;

  auto GetPosition() const -> glm::vec3 { return cameraPos; }
  auto GetFront() const -> glm::vec3 { return cameraFront; }
  auto GetUp() const -> glm::vec3 { return cameraUp; }
  auto SetPosition(glm::vec3 position) -> void { cameraPos = position; }
  auto SetFront(const glm::vec3 front) -> void { cameraFront = front; }
};

#endif  // CAMERA_H