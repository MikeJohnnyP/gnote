#pragma once

#include "Camera.h"

namespace Gnote
{
class GNOTE_API OrthographicCamera : public Camera
{
  public:
    OrthographicCamera(float left, float right, float bottom, float top);
    OrthographicCamera()
    {
    }
    ~OrthographicCamera();

    const glm::mat4 &GetViewProjectionMatrix() const override
    {
        return m_ViewProjection;
    }
    const glm::mat4 &GetViewMatrix() const override
    {
        return m_View;
    }
    const glm::mat4 &GetProjectionMatrix() const override
    {
        return m_Projection;
    }

    void SetPosition(const glm::vec3 &position) override;
    void SetRotation(const float rotation) override;
    void SetProjection(const glm::mat4 &projection) override;

    const glm::vec3 &GetPosition() const override
    {
        return m_Position;
    }
    const float &GetRotation() const override
    {
        return m_Rotation;
    }

  private:
    void CalculateViewProjectionMatrix();

  private:
    glm::mat4 m_Projection;
    glm::mat4 m_View;
    glm::mat4 m_ViewProjection;

    glm::vec3 m_Position;
    float m_Rotation;
};
} // namespace Gnote
