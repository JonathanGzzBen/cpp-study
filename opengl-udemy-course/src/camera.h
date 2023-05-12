#ifndef CAMERA_H
#define CAMERA_H

// clang-format off
#include <gl/glew.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
 public:
  Camera() = default;
  Camera(glm::vec3 position, glm::vec3 world_up, GLfloat yaw, GLfloat pitch, GLfloat movement_speed, GLfloat turn_speed);
  ~Camera() = default;

  void KeyControl(bool* keys, GLfloat delta_time);
  void MouseControl(GLfloat x_change, GLfloat y_change);
  glm::mat4 CalculateViewMatrix();

 private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 world_up;

  GLfloat yaw;
  GLfloat pitch;

  GLfloat movement_speed;
  GLfloat turn_speed;

  void update();
};

#endif  // CAMERA_H