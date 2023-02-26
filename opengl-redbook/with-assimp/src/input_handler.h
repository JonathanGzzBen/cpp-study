#ifndef CREATIVE_CONTROLS_H
#define CREATIVE_CONTROLS_H
#include <gl/glew.h>

#include "GLFW/glfw3.h"
#include "camera.h"

class InputHandler {
 private:
  /* CursorPos*/
  Camera *camera;
  bool firstMouse = true;
  float lastX = 350;
  float lastY = 350;
  float yaw = -90.0f;
  float pitch = 0.0f;

 public:
  /* Scroll */
  float fov = 45.0f;
  bool pressed[GLFW_KEY_MENU + 1];  // last key macro
  static void CursorPosCallback(GLFWwindow *window, double xPos, double yPos);
  static void ScrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  InputHandler(Camera *camera = nullptr) : camera{camera} {
    for (size_t i = 0; i < GLFW_KEY_MENU + 1; i++) {
      pressed[i] = false;
    }
  }
  ~InputHandler() = default;
  auto GetCamera() -> Camera * { return camera; }
};

#endif  // CREATIVE_CONTROLS_H