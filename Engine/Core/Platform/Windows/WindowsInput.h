#pragma once
#include "Core/Input.h"
#include "Core/InputPlatform.h"

struct GLFWwindow;

namespace Gnote
{
class WindowsKeyboardInput : public KeyInputPlatform
{
  public:
    WindowsKeyboardInput();
    virtual ~WindowsKeyboardInput();
    virtual EKeyState GetState(int32_t keyCode) const override;
    virtual bool IsPressed(int32_t keyCode) const override;
    virtual bool IsHeld(int32_t keyCode) const override;
    virtual bool IsReleased(int32_t keyCode) const override;

  private:
    GLFWwindow *window;
};

class WindowMouseInput : public MouseInputPlatform
{
  public:
    WindowMouseInput();
    virtual ~WindowMouseInput();
    virtual EKeyState GetState(int32_t keyCode) const override;
    virtual bool IsPressed(int32_t keyCode) const override;
    virtual bool IsHeld(int32_t keyCode) const override;
    virtual bool IsReleased(int32_t keyCode) const override;

  private:
    GLFWwindow *window;
};
} // namespace Gnote
