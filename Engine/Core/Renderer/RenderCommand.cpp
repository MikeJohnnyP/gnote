#include "RenderCommand.h"
#include "Core/Platform/OpenGL/OpenGLRendererAPI.h"
#include "pch.h"

namespace Gnote
{
Ref<RendererAPI> RenderCommand::s_RendererAPI = std::make_shared<OpenGLRendererAPI>();
}
