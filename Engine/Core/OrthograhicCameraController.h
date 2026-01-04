#pragma once

#include "Core/Event/ApplicationEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Renderer/Camera/OrthographicCamera.h"
#include "Core/TimeSteps.h"
#include "pch.h"

namespace Gnote
{
class OrthographicCameraController
{
  public:
    OrthographicCameraController(float aspectRatio, bool rotation, bool mouseControl);
    virtual ~OrthographicCameraController();

    void OnUpdate(TimeSteps &ts);
    void OnEvent(Event &e);

    const OrthographicCamera &GetCamera() const
    {
        return m_Camera;
    }
    inline float GetCameraMovementSpeed() const
    {
        return m_CameraMovementSpeed;
    }
    inline float GetCameraRotation() const
    {
        return m_CameraRotation;
    }
    inline float GetCameraRotateSpeed() const
    {
        return m_CameraRotateSpeed;
    }

  private:
    bool MouseScrollZoom(MouseScroll &e);
    bool MouseCameraControl(MouseMoved &e);
    bool WindowResize(WindowResizeEvent &e);

  private:
    bool m_IsRotate;
    bool m_IsMouseControl;
    float m_ZoomLevel;
    float m_CameraRotation;
    float m_CameraRotateSpeed;
    float m_CameraMovementSpeed;
    float m_Sensitivity;
    float m_aspectRatio;
    TimeSteps m_ts;
    glm::vec3 m_CameraPos;
    OrthographicCamera m_Camera;
};
} // namespace Gnote
