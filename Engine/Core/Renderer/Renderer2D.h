#pragma once
#include "Camera/Camera.h"
#include "RenderCommand.h"
#include "Texture.h"
#include "pch.h"

namespace Gnote
{
class Renderer2D
{
  public:
    static void Init();
    static void Shudown();
    static void Resizing(uint32_t width, uint32_t height);
    static void BeginScene(const Camera &camera);
    static void EndScene();
    static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture);
    static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture);
    static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
    static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);

    inline static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    }

  private:
};
} // namespace Gnote
