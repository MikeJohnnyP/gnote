#include "Renderer.h"
#include "Core/Platform/OpenGL/OpenGLShader.h"
#include "pch.h"
#include <glm/gtc/type_ptr.hpp>

namespace Gnote {
void Renderer::Init() { RenderCommand::Init(); }

void Renderer::Shutdown() {}

void Renderer::Resizing(uint32_t width, uint32_t height) {
  RenderCommand::ViewFrame(width, height);
}

void Renderer::BeginScene(const Camera &camera,
                          const std::initializer_list<Ref<Shader>> &shaders) {
  for (auto &shader : shaders) {
    shader->Bind();
    DYNAMIC_CAST(shader, OpenGLShader)
        ->UniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    shader->Unbind();
  }
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<VertexArray> &vertexArray,
                      const Ref<Shader> &shader, const glm::mat4 &transform) {
  shader->Bind();
  DYNAMIC_CAST(shader, OpenGLShader)->UniformMat4("u_ModelMatrix", transform);
  vertexArray->Bind();
  RenderCommand::DrawArrays(vertexArray);
}
} // namespace Gnote
