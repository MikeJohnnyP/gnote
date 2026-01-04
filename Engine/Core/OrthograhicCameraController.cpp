#include "OrthograhicCameraController.h"
#include "Core/Application.h"
#include "Core/Logger/Logger.h"
#include "pch.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Gnote {
OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool rotation,
                                                           bool mouseControl)
    : m_IsRotate(rotation), m_IsMouseControl(mouseControl), m_ZoomLevel(1),
      m_CameraRotation(0.0f), m_CameraRotateSpeed(180.0f),
      m_CameraMovementSpeed(5), m_Sensitivity(0.25f),
      m_aspectRatio(aspectRatio), m_CameraPos({0, 0, 0}),
      m_Camera(OrthographicCamera(-(m_aspectRatio * m_ZoomLevel),
                                  m_aspectRatio * m_ZoomLevel, -m_ZoomLevel,
                                  m_ZoomLevel)) {}
OrthographicCameraController::~OrthographicCameraController() {}
void OrthographicCameraController::OnUpdate(TimeSteps &ts) {
  m_ts = ts;
  if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
          GNOTE_KEY_A)) {
    m_CameraPos.x -= m_CameraMovementSpeed * ts.GetTime();
    m_Camera.SetPosition(m_CameraPos);
  } else if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
                 GNOTE_KEY_D)) {
    m_CameraPos.x += m_CameraMovementSpeed * ts.GetTime();
    m_Camera.SetPosition(m_CameraPos);
  }

  if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
          GNOTE_KEY_W)) {
    m_CameraPos.y += m_CameraMovementSpeed * ts.GetTime();
    m_Camera.SetPosition(m_CameraPos);
  } else if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
                 GNOTE_KEY_S)) {
    m_CameraPos.y -= m_CameraMovementSpeed * ts.GetTime();
    m_Camera.SetPosition(m_CameraPos);
  }

  if (m_IsRotate) {
    if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
            GNOTE_KEY_Q)) {
      m_CameraRotation -= m_CameraRotateSpeed * ts.GetTime();
      m_Camera.SetRotation(m_CameraRotation);
    } else if (Application::GetInstance()->GetInputState()->Keyboard->IsPressed(
                   GNOTE_KEY_E)) {
      m_CameraRotation += m_CameraRotateSpeed * ts.GetTime();
      m_Camera.SetRotation(m_CameraRotation);
    }
  }

  m_CameraMovementSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatcher<MouseScroll>(
      GNOTE_EVENT_BIND(OrthographicCameraController::MouseScrollZoom));
  dispatcher.Dispatcher<MouseMoved>(
      GNOTE_EVENT_BIND(OrthographicCameraController::MouseCameraControl));
  dispatcher.Dispatcher<WindowResizeEvent>(
      GNOTE_EVENT_BIND(OrthographicCameraController::WindowResize));
}

bool OrthographicCameraController::MouseScrollZoom(MouseScroll &e) {
  m_ZoomLevel -=
      Application::GetInstance()->GetInputState()->Mouse->GetScrollY();
  m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
  m_Camera.SetProjection(glm::ortho(-(m_aspectRatio * m_ZoomLevel),
                                    m_aspectRatio * m_ZoomLevel, -m_ZoomLevel,
                                    m_ZoomLevel));
  return false;
}

bool OrthographicCameraController::MouseCameraControl(MouseMoved &e) {
  if (m_IsMouseControl) {
    if (Application::GetInstance()->GetInputState()->Mouse->IsPressed(
            GNOTE_MOUSE_BUTTON_LEFT)) {
      m_CameraPos.x -=
          Application::GetInstance()->GetInputState()->Mouse->GetOffsetX() *
          m_ts * m_Sensitivity * m_ZoomLevel;
      m_CameraPos.y +=
          Application::GetInstance()->GetInputState()->Mouse->GetOffsetY() *
          m_ts * m_Sensitivity * m_ZoomLevel;
      m_Camera.SetPosition(m_CameraPos);
      return true;
    }
  }
  return false;
}
bool OrthographicCameraController::WindowResize(WindowResizeEvent &e) {
  m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
  m_Camera.SetProjection(glm::ortho(-(m_aspectRatio * m_ZoomLevel),
                                    m_aspectRatio * m_ZoomLevel, -m_ZoomLevel,
                                    m_ZoomLevel));
  return false;
}
} // namespace Gnote
