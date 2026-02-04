#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "pch.h"
#include "Core/Renderer/GraphicsContext.h"

namespace Gnote
{
class GNOTE_API Win32OpenGLContext : public GraphicsContext
{
  public:
    explicit Win32OpenGLContext(const HINSTANCE& hInstance, const HDC& hDC);
    ~Win32OpenGLContext();
    virtual void Init();
    virtual void SwapBuffer();

  private:
    HINSTANCE m_Hinstance;
    HDC m_hDC;
    HGLRC m_Context;
};
} // namespace Gnote
