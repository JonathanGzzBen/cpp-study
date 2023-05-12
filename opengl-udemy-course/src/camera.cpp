#include "camera.h"

#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, glm::vec3 world_up, GLfloat yaw,
               GLfloat pitch, GLfloat movement_speed, GLfloat turn_speed)
    : position{position},
      world_up{world_up},
      yaw{yaw},
      pitch{pitch},
      movement_speed{movement_speed},
      turn_speed{turn_speed},
      front{glm::vec3(0.0f, 0.0f, -1.0f)} {
  update();
}

void Camera::KeyControl(bool* keys, GLfloat delta_time) {
  GLfloat velocity = movement_speed * delta_time;

  if (keys[GLFW_KEY_W]) position += front * velocity;
  if (keys[GLFW_KEY_S]) position -= front * velocity;
  if (keys[GLFW_KEY_D]) position += right * velocity;
  if (keys[GLFW_KEY_A]) position -= right * velocity;
}

void Camera::MouseControl(GLfloat x_change, GLfloat y_change) {
  x_change *= turn_speed;
  y_change *= turn_speed;

  yaw += x_change;
  pitch += y_change;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  update();
}

glm::mat4 Camera::CalculateViewMatrix() {
  return glm::lookAt(position, position + front, up);
}

void Camera::update() {
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(front);

  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}
