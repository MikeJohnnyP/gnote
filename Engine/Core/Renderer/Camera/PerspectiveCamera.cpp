#include "PerspectiveCamera.h"
#include "pch.h"
#include <glm/matrix.hpp>

namespace Gnote {
PerspectiveCamera::PerspectiveCamera(const glm::vec3 &cameraPos,
                                     float aspectRatio)
    : m_Fov(45.f), m_AspectRatio(aspectRatio),
      m_CameraOrientation(glm::vec3(0.0f, 0.0f, 0.0f)), m_CameraPos(cameraPos),
      m_View(glm::mat4(1.0f)),
      m_Projection(
          glm::perspective(glm::radians(m_Fov), aspectRatio, 0.1f, 1000.f)),
      m_ViewProjection(glm::mat4(1.0f)) {
  CalculateViewProjectionMatrix();
  // m_ViewProjection = m_Projection;
}

PerspectiveCamera::~PerspectiveCamera() {}

const glm::mat4 &PerspectiveCamera::GetViewProjectionMatrix() const {
  return m_ViewProjection;
}

const glm::mat4 &PerspectiveCamera::GetViewMatrix() const { return m_View; }

const glm::mat4 &PerspectiveCamera::GetProjectionMatrix() const {
  return m_Projection;
}

void PerspectiveCamera::SetPosition(const glm::vec3 &position) {
  m_CameraPos = position;
  CalculateViewProjectionMatrix();
}

void PerspectiveCamera::SetRotation(const float rotation) {}

void PerspectiveCamera::SetProjection(const glm::mat4 &projection) {
  m_Projection = projection;
  m_ViewProjection = m_Projection * m_View;
}

const glm::vec3 &PerspectiveCamera::GetPosition() const { return m_CameraPos; }

const float &PerspectiveCamera::GetRotation() const { return 0.f; }

const glm::quat &PerspectiveCamera::GetCameraOrientaion() const {
  return m_CameraOrientation;
}

void PerspectiveCamera::SetFov(const float &fov) { m_Fov = fov; }

void PerspectiveCamera::CalculateViewProjectionMatrix() {
  glm::mat4 rotation = glm::mat4_cast(glm::conjugate(m_CameraOrientation));
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_CameraPos);
  m_View = rotation * translation;

  m_ViewProjection = m_Projection * m_View;
}
} // namespace Gnote
