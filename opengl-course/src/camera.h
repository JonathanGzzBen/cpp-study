#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include <array>
#include <glm/glm.hpp>

class Camera {
 public:
  Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw,
         GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
  ~Camera() = default;

  void keyControl(std::array<bool, 1024>* keys, GLfloat deltaTime);
  void mouseControl(GLfloat xChange, GLfloat yChange);
  glm::mat4 calculateViewMatrix();

 private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  GLfloat yaw;
  GLfloat pitch;

  GLfloat moveSpeed;
  GLfloat turnSpeed;

  void update();
};

#endif  // CAMERA_H