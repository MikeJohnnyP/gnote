#pragma once

#include "Core/Renderer/Camera/Camera.h"
#include <glm/gtc/quaternion.hpp>

namespace Gnote
{
class PerspectiveCamera : public Camera
{
  public:
    PerspectiveCamera(const glm::vec3 &cameraPos, float aspectRatio);
    virtual ~PerspectiveCamera();
    virtual const glm::mat4 &GetViewProjectionMatrix() const override;
    virtual const glm::mat4 &GetViewMatrix() const override;
    virtual const glm::mat4 &GetProjectionMatrix() const override;

    virtual void SetPosition(const glm::vec3 &position) override;
    virtual void SetRotation(const float rotation) override;
    virtual void SetProjection(const glm::mat4 &projection) override;

    virtual const glm::vec3 &GetPosition() const override;
    virtual const float &GetRotation() const override;

    const glm::quat &GetCameraOrientaion() const;
    void SetFov(const float &fov);

  private:
    void CalculateViewProjectionMatrix();

  private:
    float m_Fov;
    float m_AspectRatio;

    glm::quat m_CameraOrientation;
    glm::vec3 m_CameraPos;

    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::mat4 m_ViewProjection;
};
} // namespace Gnote
