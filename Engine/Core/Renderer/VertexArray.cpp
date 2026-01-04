#include "VertexArray.h"
#include "Core/Logger/Logger.h"
#include "Core/Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "pch.h"

namespace Gnote {
Ref<VertexArray> VertexArray::Create() {
  RendererAPI::API type = Renderer::GetAPI();
  switch (type) {
  case RendererAPI::API::None: {
    GNOTE_ASSERT(false, "unknown Renderer API");
    return nullptr;
  }
  case RendererAPI::API::OpenGL: {
    return std::make_shared<OpenGLVertexArray>();
  }
  }
  return nullptr;
}
} // namespace Gnote
