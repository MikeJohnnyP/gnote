#pragma once

#include "RendererAPI.h"
#include "pch.h"

namespace Gnote
{
class GNOTE_API RenderCommand
{
  public:
    inline static void Init()
    {
        s_RendererAPI->Init();
    }
    inline static void SetClearColor(const glm::vec4 &color)
    {
        s_RendererAPI->ClearColor(color);
    }

    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(const Ref<VertexArray> &vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }

    inline static void DrawArrays(const Ref<VertexArray> &vertexArray)
    {
        s_RendererAPI->DrawArrays(vertexArray);
    }

    inline static void ViewFrame(uint32_t width, uint32_t height)
    {
        s_RendererAPI->ViewFrame(width, height);
    }

  private:
    static Ref<RendererAPI> s_RendererAPI;
};
} // namespace Gnote
