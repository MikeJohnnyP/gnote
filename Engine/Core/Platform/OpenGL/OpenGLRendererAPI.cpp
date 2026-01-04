#include "OpenGLRendererAPI.h"
#include "pch.h"
#include <glad/glad.h>

namespace Gnote {
void OpenGLRendererAPI::Init() const {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::ClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.b, color.g, color.a);
}

void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray) {
  glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(),
                 GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawArrays(const Ref<VertexArray> &vertexArray) {
  glDrawArrays(GL_TRIANGLES, 0,
               vertexArray->GetVertexBuffer().at(0)->GetCount());
}

void OpenGLRendererAPI::ViewFrame(uint32_t width, uint32_t height) {
  glViewport(0, 0, width, height);
}
} // namespace Gnote
