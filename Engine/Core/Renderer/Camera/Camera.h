#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace Gnote {
class GNOTE_API Camera {
public:
  Camera() = default;
  virtual ~Camera() = default;
  virtual const glm::mat4 &GetViewProjectionMatrix() const = 0;
  virtual const glm::mat4 &GetViewMatrix() const = 0;
  virtual const glm::mat4 &GetProjectionMatrix() const = 0;

  virtual void SetPosition(const glm::vec3 &position) = 0;
  virtual void SetRotation(const float rotation) = 0;
  virtual void SetProjection(const glm::mat4 &projection) = 0;

  virtual const glm::vec3 &GetPosition() const = 0;
  virtual const float &GetRotation() const = 0;

private:
};
} // namespace Gnote
