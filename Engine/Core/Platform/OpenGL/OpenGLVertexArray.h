#pragma once
#include "Core/Renderer/VertexArray.h"

namespace Gnote {
class OpenGLVertexArray : public VertexArray {
public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();
  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
  virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

  virtual std::vector<Ref<VertexBuffer>> &GetVertexBuffer() override {
    return m_VertexBuffer;
  }
  virtual Ref<IndexBuffer> &GetIndexBuffer() override { return m_IndexBuffer; }

private:
  uint32_t m_VAO;
  std::vector<Ref<VertexBuffer>> m_VertexBuffer;
  Ref<IndexBuffer> m_IndexBuffer;
};
} // namespace Gnote
