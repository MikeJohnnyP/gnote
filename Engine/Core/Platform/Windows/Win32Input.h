#pragma once
#include "Core/Input.h"
#include "Core/InputPlatform.h"

namespace Gnote
{
class Win32KeyboardInput : public KeyInputPlatform
{
  public:
    Win32KeyboardInput();
    virtual ~Win32KeyboardInput();
    virtual EKeyState GetState(int32_t keyCode) const override;
    virtual bool IsPressed(int32_t keyCode) const override;
    virtual bool IsHeld(int32_t keyCode) const override;
    virtual bool IsReleased(int32_t keyCode) const override;

  private:
};

class Win32MouseInput : public MouseInputPlatform
{
  public:
    Win32MouseInput();
    virtual ~Win32MouseInput();
    virtual EKeyState GetState(int32_t keyCode) const override;
    virtual bool IsPressed(int32_t keyCode) const override;
    virtual bool IsHeld(int32_t keyCode) const override;
    virtual bool IsReleased(int32_t keyCode) const override;

  private:
};
} // namespace Gnote
