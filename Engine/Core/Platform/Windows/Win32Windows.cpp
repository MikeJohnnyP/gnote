#include "Win32Windows.h"
#include "Core/Logger/Logger.h"
#include <cstddef>
#include <errhandlingapi.h>
#include <string>
#include <winuser.h>

namespace Gnote
{

LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
    {
        if ((HIWORD(lParam) & KF_REPEAT) != KF_REPEAT)
        {
            CORE_LOG_INFO("Key down {}", (int)wParam);
        }
        break;
    }
    case WM_KEYUP:
    {
        // Key Up Event.
        CORE_LOG_INFO("Key up {}", (int)wParam);
        break;
    }
    case WM_MOUSEMOVE:
    {
        // Mouse Move Event.
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    {
        // Mouse Button Down Event.
        // To make sure the input is synonymous in both linux & windows.
        // 1 - LMB, 2 - MMB, 3 - RMB
        uint32_t button = (uMsg == WM_RBUTTONDOWN) ? 3 : (uMsg == WM_MBUTTONDOWN ? 2 : 1);
        break;
    }
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        // Mouse Button Up Event.
        uint32_t button = (uMsg == WM_RBUTTONUP) ? 3 : (uMsg == WM_MBUTTONUP ? 2 : 1);
        break;
    }
    case WM_SIZE:
    {
        // Window Resize Event.
        uint32_t width = LOWORD(lParam);  // Macro to get the low-order word.
        uint32_t height = HIWORD(lParam); // Macro to get the high-order word.
        break;
    }
    case WM_PAINT:
    {
        // Paint all the area again.
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetDCBrushColor(hdc, RGB(10, 20, 30));
        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(GetStockObject(DC_BRUSH)));
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
    {
        // Window Close Event.
        break;
    }
    case WM_DESTROY:
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Win32Windows::Win32Windows(const WindowSpec& spec)
    : m_hInstance(nullptr)
    , m_hWnd(nullptr)
{
    m_Win32Data.Height = spec.height;
    m_Win32Data.Width = spec.width;
    m_Win32Data.Title = spec.Title;
    m_Win32Data.Vsync = spec.Vsync;
}

bool Win32Windows::Init()
{
    WNDCLASSEXW wndClass = {};
    wndClass.cbSize = sizeof(WNDCLASSEXW);
    wndClass.lpszClassName = m_ClassName.c_str();
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = &WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = NULL;
    wndClass.lpszMenuName = NULL;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    DWORD style = WS_OVERLAPPEDWINDOW;

    RECT rect;
    rect.left = 250;
    rect.bottom = 250;
    rect.right = rect.left + m_Win32Data.Width;
    rect.top = rect.bottom + m_Win32Data.Height;

    // To make sure that our window size is the whole canvas and not the outer border.
    AdjustWindowRect(&rect, style, false);

    if (!RegisterClassExW(&wndClass))
    {
        CORE_LOG_ERROR("ERROR when register wndClass with error code {}", GetLastError());
        return GetLastError();
    }

    m_Win32Data.Width = rect.right - rect.left;
    m_Win32Data.Height = rect.top - rect.bottom;
    CORE_LOG_INFO("WIDTH & HEIGHT of Rect: {}\{}", m_Win32Data.Width, m_Win32Data.Height);

    m_hWnd = CreateWindowExW(
        0,
        m_ClassName.c_str(),
        std::wstring(m_Win32Data.Title.begin(), m_Win32Data.Title.end()).c_str(),
        style,
        rect.left,
        rect.bottom,
        m_Win32Data.Width,
        m_Win32Data.Height,
        NULL,
        NULL,
        m_hInstance,
        NULL);

    if (!m_hWnd)
    {
        CORE_LOG_ERROR("ERROR when create window with error code {}", GetLastError());
        return GetLastError();
    }

    ShowWindow(m_hWnd, SW_SHOW);

    return true;
}
void Win32Windows::Shutdown()
{
    DestroyWindow(m_hWnd);
    PostQuitMessage(0);
    UnregisterClassW(m_ClassName.c_str(), m_hInstance);
}
void Win32Windows::SwapBuffer()
{
}
void Win32Windows::PollEvent()
{
    if (!ProcessMessagesQueue())
        return;
}
bool Win32Windows::IsWindowClose()
{
    return IsWindow(m_hWnd);
}
bool Win32Windows::IsVsyncEnable()
{
    return m_Win32Data.Vsync;
}
void Win32Windows::SetFunctionCallback(const EventFn& callback)
{
}
void* Win32Windows::GetNativeWindow()
{
    return nullptr;
}
float Win32Windows::GetTime()
{
    return .0f;
}
float Win32Windows::GetTimeMiliSeconds()
{
    return .0f;
}
InputState* Win32Windows::GetInputState()
{
    return nullptr;
}

bool Win32Windows::ProcessMessagesQueue()
{
    MSG msg = {};
    while (PeekMessage(&msg, m_hWnd, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}
} // namespace Gnote
