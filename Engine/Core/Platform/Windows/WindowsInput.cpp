#include "WindowsInput.h"
#include "Core/Application.h"
#include "pch.h"
#include <GLFW/glfw3.h>

namespace Gnote {
WindowsKeyboardInput::WindowsKeyboardInput() {
  window = static_cast<GLFWwindow *>(
      Application::GetInstance()->GetWindow()->GetNativeWindow());
}

WindowsKeyboardInput::~WindowsKeyboardInput() {}

EKeyState WindowsKeyboardInput::GetState(int32_t keyCode) const {
  int action = glfwGetKey(window, keyCode);
  switch (action) {
  case GLFW_PRESS: {
    return EKeyState::PRESSED;
    break;
  }
  case GLFW_RELEASE: {
    return EKeyState::RELEASED;
    break;
  }
  case GLFW_REPEAT: {
    return EKeyState::HELD;
    break;
  }
  default: {
    return EKeyState::NONE;
    break;
  }
  }
}

bool WindowsKeyboardInput::IsPressed(int32_t keyCode) const {
  return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

bool WindowsKeyboardInput::IsHeld(int32_t keyCode) const {
  return glfwGetKey(window, keyCode) == GLFW_REPEAT;
}

bool WindowsKeyboardInput::IsReleased(int32_t keyCode) const {
  return glfwGetKey(window, keyCode) == GLFW_RELEASE;
}

WindowMouseInput::WindowMouseInput() {
  window = static_cast<GLFWwindow *>(
      Application::GetInstance()->GetWindow()->GetNativeWindow());
}

WindowMouseInput::~WindowMouseInput() {}

EKeyState WindowMouseInput::GetState(int32_t keyCode) const {
  int action = glfwGetMouseButton(window, keyCode);
  switch (action) {
  case GLFW_PRESS: {
    return EKeyState::PRESSED;
    break;
  }
  case GLFW_RELEASE: {
    return EKeyState::RELEASED;
    break;
  }
  default: {
    return EKeyState::NONE;
    break;
  }
  }
}

bool WindowMouseInput::IsPressed(int32_t keyCode) const {
  return glfwGetMouseButton(window, keyCode) == GLFW_PRESS;
}

bool WindowMouseInput::IsHeld(int32_t keyCode) const { return false; }

bool WindowMouseInput::IsReleased(int32_t keyCode) const {
  return glfwGetMouseButton(window, keyCode) == GLFW_RELEASE;
}

} // namespace Gnote
