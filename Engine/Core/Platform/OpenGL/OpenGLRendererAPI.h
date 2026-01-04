#pragma once

#include "Core/Renderer/RendererAPI.h"

namespace Gnote {
class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void Init() const override;
  virtual void ClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;
  virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
  virtual void DrawArrays(const Ref<VertexArray> &vertexArray) override;
  virtual void ViewFrame(uint32_t width, uint32_t height) override;

private:
};
} // namespace Gnote
