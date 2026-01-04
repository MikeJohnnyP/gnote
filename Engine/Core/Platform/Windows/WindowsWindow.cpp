#include "WindowsWindow.h"
#include "Core/Event/ApplicationEvent.h"
#include "Core/Event/KeyboardEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/InputPlatform.h"
#include "Core/Logger/Logger.h"
#include "Core/Platform/OpenGL/OpenGLContext.h"
#include "WindowsInput.h"
#include "pch.h"
#include <GLFW/glfw3.h>

namespace Gnote
{
KeyInputPlatform *createKeyInput()
{
    return new WindowsKeyboardInput();
}
MouseInputPlatform *createMouseInput()
{
    return new WindowMouseInput();
}

static bool GLFWInitialize = false;

Window *createWindow()
{
    WindowSpec spec = Gnote::createSpec();
    return new WindowsWindow(spec);
}

WindowsWindow::WindowsWindow(WindowSpec &spec)
{
    m_data.width = spec.width;
    m_data.height = spec.height;
    m_data.Title = spec.Title;
    m_data.vSync = spec.Vsync;
}

bool WindowsWindow::Init()
{

    if (!GLFWInitialize)
    {
        int success = glfwInit();
        GNOTE_ASSERT(success, "Failed to initialize GLFW");
        GLFWInitialize = true;
    }
    CORE_LOG_INFO("Initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwindow = glfwCreateWindow(m_data.width, m_data.height, m_data.Title.c_str(), nullptr, nullptr);
    if (m_GLFWwindow == nullptr)
    {
        GNOTE_ASSERT(false, "Cannot created m_window");
        glfwTerminate();
        return false;
    }
    CORE_LOG_INFO("Created m_window sucess");

    m_context = new OpenGLContext(m_GLFWwindow);
    m_context->Init();

    m_data.inputState.Keyboard = createKeyInput();
    m_data.inputState.Mouse = createMouseInput();

    if (m_data.vSync)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    glfwSetWindowUserPointer(m_GLFWwindow, (void *)&m_data);

    glfwSetWindowSizeCallback(m_GLFWwindow,
                              [](GLFWwindow *window, int width, int height)
                              {
                                  WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                  data.width = static_cast<unsigned int>(width);
                                  data.height = static_cast<unsigned int>(height);
                                  WindowResizeEvent e((unsigned int)data.width, (unsigned int)data.height);
                                  data.callback(e);
                              });

    static bool firstStart = true;
    glfwSetCursorPosCallback(m_GLFWwindow,
                             [](GLFWwindow *window, double xpos, double ypos)
                             {
                                 WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                                 static double LastFrameX = xpos;
                                 static double LastFrameY = ypos;

                                 double offsetX = xpos - LastFrameX;
                                 double offsetY = ypos - LastFrameY;

                                 data.inputState.Mouse->SetOffset((float)offsetX, (float)offsetY);
                                 data.inputState.Mouse->SetPosition((float)xpos, (float)ypos);

                                 MouseMoved e((float)xpos, (float)ypos);
                                 data.callback(e);

                                 LastFrameX = xpos;
                                 LastFrameY = ypos;
                             });

    glfwSetKeyCallback(m_GLFWwindow,
                       [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
                           WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                           switch (action)
                           {
                           case GLFW_PRESS:
                           {
                               KeyPressed e(key, 1);
                               data.callback(e);
                               break;
                           }
                           case GLFW_RELEASE:
                           {
                               KeyReleased e(key);
                               data.callback(e);
                               break;
                           }
                           case GLFW_REPEAT:
                           {
                               KeyPressed e(key, 1);
                               data.callback(e);
                               break;
                           }
                           }
                       });

    glfwSetMouseButtonCallback(m_GLFWwindow,
                               [](GLFWwindow *window, int button, int action, int mods)
                               {
                                   WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                   switch (action)
                                   {
                                   case GLFW_PRESS:
                                   {
                                       MouseButtonPressed e(button);
                                       data.callback(e);
                                       break;
                                   }
                                   case GLFW_RELEASE:
                                   {
                                       MouseButtonReleased e(button);
                                       data.callback(e);
                                       break;
                                   }
                                   }
                               });

    glfwSetScrollCallback(m_GLFWwindow,
                          [](GLFWwindow *window, double xoffset, double yoffset)
                          {
                              WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                              data.inputState.Mouse->SetScroll((float)xoffset, (float)yoffset);
                              MouseScroll e((float)xoffset, (float)yoffset);
                              data.callback(e);
                          });

    glfwSetCharCallback(m_GLFWwindow,
                        [](GLFWwindow *window, unsigned int codepoint)
                        {
                            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                            KeyTyped e(codepoint);
                            data.callback(e);
                        });

    return true;
}
void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_GLFWwindow);
}
void WindowsWindow::SwapBuffer()
{
    m_context->SwapBuffer();
}
void WindowsWindow::PollEvent()
{
    glfwPollEvents();
}
bool WindowsWindow::IsWindowClose()
{
    return glfwWindowShouldClose(m_GLFWwindow);
}
bool WindowsWindow::IsVsyncEnable()
{
    return m_data.vSync;
}
void WindowsWindow::SetFunctionCallback(const EventFn &callback)
{
    m_data.callback = callback;
}

void *WindowsWindow::GetNativeWindow()
{
    return (void *)m_GLFWwindow;
}

InputState *WindowsWindow::GetInputState()
{
    return &m_data.inputState;
}

float WindowsWindow::GetTime()
{
    return (float)glfwGetTime();
}

float WindowsWindow::GetTimeMiliSeconds()
{
    return (float)glfwGetTime() * 1000.0f;
}
} // namespace Gnote
