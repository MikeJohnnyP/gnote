#include "Texture.h"
#include "Core/Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"
#include "pch.h"

namespace Gnote
{
Ref<Texture2D> Texture2D::Create(const std::string &filePath)
{
    RendererAPI::API type = Renderer::GetAPI();
    switch (type)
    {
    case RendererAPI::API::None:
    {
        GNOTE_ASSERT(false, "unknown Renderer API");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
    {
        return std::make_shared<OpenGLTexture>(filePath);
    }
    }
    return nullptr;
}
Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    RendererAPI::API type = Renderer::GetAPI();
    switch (type)
    {
    case RendererAPI::API::None:
    {
        GNOTE_ASSERT(false, "unknown Renderer API");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
    {
        return std::make_shared<OpenGLTexture>(width, height);
    }
    }
    return nullptr;
}
} // namespace Gnote
