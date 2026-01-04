#pragma once
#include "Core/Renderer/Buffer.h"
namespace Gnote
{
class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(float *vertex, uint32_t size);
    ~OpenGLVertexBuffer();
    virtual void Bind() const override;
    virtual void UnBind() const override;

    virtual const BufferLayout &GetLayout() const override
    {
        return m_Layout;
    }
    virtual void SetLayout(const BufferLayout &layout) override
    {
        m_Layout = layout;
    }
    virtual uint32_t GetCount() override;

  private:
    BufferLayout m_Layout;
    uint32_t m_Count;
    uint32_t m_VBO;
};

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t *indicies, uint32_t count);
    ~OpenGLIndexBuffer();
    virtual void Bind() const override;
    virtual void UnBind() const override;
    virtual uint32_t GetCount() override;

  private:
    uint32_t m_EBO;
    uint32_t m_Count;
};
} // namespace Gnote
