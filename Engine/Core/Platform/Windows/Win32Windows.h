#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "pch.h"

#include "Core/Renderer/GraphicsContext.h"
#include "Core/Window.h"

namespace Gnote
{
class GNOTE_API Win32Windows : public Window
{
  public:
    Win32Windows(const WindowSpec& spec);
    ~Win32Windows() = default;
    virtual bool Init();
    virtual void Shutdown();
    virtual void SwapBuffer();
    virtual void PollEvent();
    virtual bool IsWindowClose();
    virtual bool IsVsyncEnable();
    virtual void SetFunctionCallback(const EventFn& callback);
    virtual void* GetNativeWindow();
    virtual float GetTime();
    virtual float GetTimeMiliSeconds();
    virtual InputState* GetInputState();

  private:
    bool ProcessMessagesQueue();
    InputState CreateInputState();

    GraphicsContext* m_context;

    HINSTANCE m_hInstance;
    HWND m_hWnd;
    HDC m_hDC;
    const std::wstring m_ClassName = L"GnoteWindowClass";

    // Windows settings specific
    struct Win32Data
    {
        uint32_t Width, Height;
        std::string Title;
        bool Vsync = false;
        EventFn Callback;
        InputState InputState;
    };

    Win32Data m_Win32Data;
};

Window* CreateWin32Window();
} // namespace Gnote
