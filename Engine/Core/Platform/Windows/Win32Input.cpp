#include "Win32Input.h"
#include "Core/Input.h"

namespace Gnote
{

Win32KeyboardInput::Win32KeyboardInput()
{
}
Win32KeyboardInput::~Win32KeyboardInput()
{
}
EKeyState Win32KeyboardInput::GetState(int32_t keyCode) const
{
    return EKeyState::PRESSED;
}
bool Win32KeyboardInput::IsPressed(int32_t keyCode) const
{
    return false;
}
bool Win32KeyboardInput::IsHeld(int32_t keyCode) const
{
    return false;
}
bool Win32KeyboardInput::IsReleased(int32_t keyCode) const
{
    return false;
}

Win32MouseInput::Win32MouseInput()
{
}
Win32MouseInput::~Win32MouseInput()
{
}
EKeyState Win32MouseInput::GetState(int32_t keyCode) const
{
    return EKeyState::PRESSED;
}
bool Win32MouseInput::IsPressed(int32_t keyCode) const
{
    return false;
}
bool Win32MouseInput::IsHeld(int32_t keyCode) const
{
    return false;
}
bool Win32MouseInput::IsReleased(int32_t keyCode) const
{
    return false;
}
} // namespace Gnote
