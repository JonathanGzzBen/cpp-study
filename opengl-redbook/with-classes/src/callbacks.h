#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <GL/glew.h>

#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"

namespace Callbacks {};  // namespace Callbacks

namespace Callbacks::FramebufferSize {

static auto ResizeViewport(GLFWwindow* window, int width, int height) {
  int frame_side_size = (width < height) ? width : height;
  glViewport(0, 0, frame_side_size, frame_side_size);
}

}  // namespace Callbacks::FramebufferSize

namespace Callbacks::Scroll {

float fov = 45.0f;
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  fov -= (float)yoffset;
  if (fov < 1.0f) fov = 1.0f;
  if (fov > 45.0f) fov = 45.0f;
}
}  // namespace Callbacks::Scroll

namespace Callbacks::CursorPos {

bool firstMouse = true;
float lastX = 350;
float lastY = 350;
float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
  if (firstMouse) {
    lastX = static_cast<float>(xPos);
    lastY = static_cast<float>(yPos);
    firstMouse = false;
  }

  float xOffset = static_cast<float>(xPos) - lastX;
  float yOffset = lastY - static_cast<float>(yPos);
  lastX = static_cast<float>(xPos);
  lastY = static_cast<float>(yPos);

  float sensitivity = 0.1f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;

  pitch = (pitch > 89.0f) ? 89.0f : pitch;
  pitch = (pitch < -89.0f) ? -89.0f : pitch;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}

}  // namespace Callbacks::CursorPos

#endif  // CALLBACKS_H