#include "input_handler.h"

#include "window.h"

void InputHandler::CursorPosCallback(GLFWwindow* window, double xPos,
                                     double yPos) {
  auto input_handler =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))
          ->GetControls();
  if (input_handler->firstMouse) {
    input_handler->lastX = static_cast<float>(xPos);
    input_handler->lastY = static_cast<float>(yPos);
    input_handler->firstMouse = false;
  }

  float xOffset = static_cast<float>(xPos) - input_handler->lastX;
  float yOffset = input_handler->lastY - static_cast<float>(yPos);
  input_handler->lastX = static_cast<float>(xPos);
  input_handler->lastY = static_cast<float>(yPos);

  float sensitivity = 0.1f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  input_handler->yaw += xOffset;
  input_handler->pitch += yOffset;

  input_handler->pitch =
      (input_handler->pitch > 89.0f) ? 89.0f : input_handler->pitch;
  input_handler->pitch =
      (input_handler->pitch < -89.0f) ? -89.0f : input_handler->pitch;

  glm::vec3 direction;
  direction.x = cos(glm::radians(input_handler->yaw)) *
                cos(glm::radians(input_handler->pitch));
  direction.y = sin(glm::radians(input_handler->pitch));
  direction.z = sin(glm::radians(input_handler->yaw)) *
                cos(glm::radians(input_handler->pitch));

  input_handler->GetCamera()->SetFront(glm::normalize(direction));
}

void InputHandler::ScrollCallback(GLFWwindow* window, double xoffset,
                                  double yoffset) {
  auto input_handler =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))
          ->GetControls();
  input_handler->fov -= (float)yoffset;
  if (input_handler->fov < 1.0f) input_handler->fov = 1.0f;
  if (input_handler->fov > 45.0f) input_handler->fov = 45.0f;
}

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode,
                               int action, int mods) {
  auto input_handler =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))
          ->GetControls();
  if (key == GLFW_KEY_UNKNOWN) return;
  if (action == GLFW_PRESS)
    input_handler->pressed[key] = true;
  else if (action == GLFW_RELEASE)
    input_handler->pressed[key] = false;
}
