#pragma once
#include "Core/Renderer/GraphicsContext.h"
#include "pch.h"

struct GLFWwindow;

namespace Gnote {
class OpenGLContext : public GraphicsContext {
public:
  OpenGLContext(GLFWwindow *window);
  virtual void Init() override;
  virtual void SwapBuffer() override;

private:
  GLFWwindow *m_WindowHandle;
};
} // namespace Gnote
