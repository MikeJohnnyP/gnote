#pragma once
#include "Camera/Camera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "pch.h"

namespace Gnote
{
enum class GNOTE_API DrawType
{
    Buffer,
    Index
};

class GNOTE_API Renderer
{
  public:
    static void Init();
    static void Shutdown();
    static void Resizing(uint32_t width, uint32_t height);
    static void BeginScene(const Camera &camera, const std::initializer_list<Ref<Shader>> &shaders);
    static void EndScene();

    static void Submit(const Ref<VertexArray> &vertexArray, const Ref<Shader> &shader,
                       const glm::mat4 &transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    }

  private:
};
} // namespace Gnote
