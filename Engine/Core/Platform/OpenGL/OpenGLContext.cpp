#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "pch.h"
#include "OpenGLContext.h"
#include "Core/Logger/Logger.h"

namespace Gnote
{
OpenGLContext::OpenGLContext(GLFWwindow *window) : m_WindowHandle(window)
{
    GNOTE_ASSERT(m_WindowHandle, "m_WindowHandle is null");
}
void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int sucess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!sucess)
    {
        GNOTE_ASSERT(false, "initialize Glad failed");
        glfwTerminate();
        return;
    }
    CORE_LOG_INFO("Load Glad Sucess");
}
void OpenGLContext::SwapBuffer()
{
    glfwSwapBuffers(m_WindowHandle);
}
} // namespace Gnote
