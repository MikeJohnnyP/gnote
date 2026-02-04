#include "Win32OpenGLContext.h"
#include "Core/Logger/Logger.h"
#include "Core/OpenGLLoader.h"
#include <gl/GL.h>
#include <opengl/wglext.h>
#include "opengl/glcorearb.h"
#include "pch.h"

namespace Gnote
{
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;

template <class T>
void ResovleGlFunction(T& function, const std::string& name)
{
    const auto address = ::wglGetProcAddress(name.c_str());
    GNOTE_CORE_ASSERT(address, "could not resolve {}", name);
    std::memcpy(std::addressof(function), &address, sizeof(T));
}

HGLRC InitOpenGL(HDC hdc)
{
    int pixel_format_attribs[]{
        WGL_DRAW_TO_WINDOW_ARB,
        GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,
        GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,
        GL_TRUE,
        WGL_ACCELERATION_ARB,
        WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,
        WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,
        32,
        WGL_DEPTH_BITS_ARB,
        24,
        WGL_STENCIL_BITS_ARB,
        8,
        WGL_SAMPLE_BUFFERS_ARB,
        GL_FALSE,
        WGL_SAMPLES_ARB,
        0,
        0};

    auto pixel_format = 0;
    auto num_formats = UINT{};

    wglChoosePixelFormatARB(hdc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    if (pixel_format == 0)
    {
        GNOTE_CORE_ASSERT(false, "Failed to choose pixel format");
        return nullptr;
    }

    auto pfd = PIXELFORMATDESCRIPTOR{};
    auto const describePixelFormatResult = DescribePixelFormat(hdc, pixel_format, sizeof(pfd), &pfd);

    if (describePixelFormatResult == 0)
    {
        GNOTE_CORE_ASSERT(false, "Failed to describe pixel format");
        return nullptr;
    }

    auto const setPixelFormatResult = SetPixelFormat(hdc, pixel_format, &pfd);

    if (!setPixelFormatResult)
    {
        GNOTE_CORE_ASSERT(false, "Failed to set pixel format");
        return nullptr;
    }

    int gl_attribs[]{
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        4,
        WGL_CONTEXT_MINOR_VERSION_ARB,
        6,
        WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    auto context = wglCreateContextAttribsARB(hdc, 0, gl_attribs);
    GNOTE_CORE_ASSERT(context, "Failed to create wgl context");

    if (!wglMakeCurrent(hdc, context))
    {
        GNOTE_CORE_ASSERT(false, "Couldn't make a current openGL context");
        return nullptr;
    }

    return context;
}

void ResolveGlobalGlFunction()
{
#define RESOLVE(TYPE, NAME) ResovleGlFunction(NAME, #NAME);

    FOR_OPENGL_FUNCTIONS(RESOLVE)
}

auto APIENTRY OpenGlDebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei,
    const GLchar* message,
    const void*) -> void
{
    CORE_LOG_ERROR("{} {} {} {} {}", source, type, id, severity, message);
}
Win32OpenGLContext::Win32OpenGLContext(const HINSTANCE& hInstance, const HDC& hDC)
    : m_Hinstance(hInstance)
    , m_hDC(hDC)
    , m_Context(nullptr)
{
}

Win32OpenGLContext::~Win32OpenGLContext()
{
}

void Win32OpenGLContext::Init()
{
    auto wc = WNDCLASSA{};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = ::DefWindowProc;
    wc.hInstance = m_Hinstance;
    wc.lpszClassName = "Dummy openGL window";
    auto const regiterWnd = RegisterClassA(&wc);
    if (!regiterWnd)
    {
        GNOTE_CORE_ASSERT(
            regiterWnd,
            "ERROR when register Dummy openGL windows with error code {}",
            GetLastError());
        return;
    }
    auto dummy_window = CreateWindowExA(
        0,
        wc.lpszClassName,
        wc.lpszClassName,
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        wc.hInstance,
        0);
    if (!dummy_window)
    {
        GNOTE_ASSERT(!dummy_window, "ERROR when create dummy window with error code {}", GetLastError());
        return;
    }
    auto fakeDc = GetDC(dummy_window);
    if (!fakeDc)
    {
        GNOTE_ASSERT(fakeDc, "ERROR when create fakeDc with error code {}", GetLastError());
        return;
    }
    auto pfd = PIXELFORMATDESCRIPTOR{};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    auto pixel_format = ChoosePixelFormat(fakeDc, &pfd);
    GNOTE_CORE_ASSERT(pixel_format != 0, "Failed to choose pixel format");
    auto pixelFormatSuccess = SetPixelFormat(fakeDc, pixel_format, &pfd) == TRUE;
    GNOTE_CORE_ASSERT(pixelFormatSuccess == TRUE, "Failed to set pixel format");
    const auto dummyContext = wglCreateContext(fakeDc);
    GNOTE_CORE_ASSERT(dummyContext, "Failed to create wgl context");
    auto wglMakeCurrentSuccess = wglMakeCurrent(fakeDc, dummyContext);
    GNOTE_CORE_ASSERT(wglMakeCurrentSuccess == TRUE, "Couldn't make a current openGL context");

    // Resolve WGL extension functions
    ResovleGlFunction(wglCreateContextAttribsARB, "wglCreateContextAttribsARB");
    ResovleGlFunction(wglChoosePixelFormatARB, "wglChoosePixelFormatARB");

    // create real OpenGL context for main window
    m_Context = InitOpenGL(m_hDC);

    ResolveGlobalGlFunction();

    const auto* vendor = ::glGetString(GL_VENDOR);
    const auto* renderer = ::glGetString(GL_RENDERER);
    const auto* version = ::glGetString(GL_VERSION);
    const auto* shadingLangguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    CORE_LOG_INFO("OpenGL Info:");
    CORE_LOG_INFO("  Vendor: {}", reinterpret_cast<const char*>(vendor));
    CORE_LOG_INFO("  Renderer: {}", reinterpret_cast<const char*>(renderer));
    CORE_LOG_INFO("  Version: {}", reinterpret_cast<const char*>(version));
    CORE_LOG_INFO("  Shading language: {}", reinterpret_cast<const char*>(shadingLangguageVersion));

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGlDebugCallback, nullptr);

    // Cleanup dummy resources
    wglMakeCurrent(fakeDc, nullptr);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummy_window, fakeDc);
    DestroyWindow(dummy_window);
    UnregisterClassA(wc.lpszClassName, m_Hinstance);

    if (!wglMakeCurrent(m_hDC, m_Context))
    {
        GNOTE_CORE_ASSERT(false, "Failed to make real OpenGL context current after cleanup");
    }
}

void Win32OpenGLContext::SwapBuffer()
{
    SwapBuffers(m_hDC);
}

} // namespace Gnote
