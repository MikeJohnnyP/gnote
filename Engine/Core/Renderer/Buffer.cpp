#include "Buffer.h"
#include "Core/Logger/Logger.h"
#include "Core/Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "pch.h"

namespace Gnote
{
Ref<VertexBuffer> VertexBuffer::create(float *vertex, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        GNOTE_ASSERT(false, "Not Support API");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertex, size);
    }
    GNOTE_ASSERT(false, "unknown renderer API");
    return nullptr;
}
Ref<IndexBuffer> IndexBuffer::create(uint32_t *indicies, uint32_t count)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        GNOTE_ASSERT(false, "Not Support API");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indicies, count);
    }
    GNOTE_ASSERT(false, "unknown renderer API");
    return nullptr;
}

} // namespace Gnote
