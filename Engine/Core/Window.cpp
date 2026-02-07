#include "Window.h"
#ifdef _WIN32
#include "Core/Platform/Windows/Win32Windows.h"
#else
#include "Core/Platform/Windows/WindowsWindow.h"
#endif

namespace Gnote
{
Window* createWindow()
{
    WindowSpec spec = Gnote::createSpec();
#ifdef _WIN32
    return new Win32Windows(spec);
#else
    return new WindowsWindow(spec);
#endif
}
}; // namespace Gnote
