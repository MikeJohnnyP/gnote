#include "OrthographicCamera.h"
#include "pch.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Gnote
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_Projection(glm::ortho(left, right, bottom, top)), m_View(glm::mat4(1.0f)), m_Rotation(0.0f),
      m_Position(glm::vec3(0.f))
{
    m_ViewProjection = m_Projection * m_View;
}
OrthographicCamera::~OrthographicCamera()
{
}
void OrthographicCamera::SetPosition(const glm::vec3 &position)
{
    m_Position = position;
    CalculateViewProjectionMatrix();
}
void OrthographicCamera::SetRotation(const float rotation)
{
    m_Rotation = rotation;
    CalculateViewProjectionMatrix();
}

void OrthographicCamera::SetProjection(const glm::mat4 &projection)
{
    m_Projection = projection;
    // CalculateViewProjectionMatrix();
    m_ViewProjection = m_Projection * m_View;
}

void OrthographicCamera::CalculateViewProjectionMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_View = glm::inverse(transform);

    m_ViewProjection = m_Projection * m_View;
}
} // namespace Gnote
