#pragma once
#include "Input.h"
#include "pch.h"

namespace Gnote
{
class GNOTE_API KeyInputPlatform
{
  public:
    virtual ~KeyInputPlatform() = default;

    inline int32_t GetValue(int32_t keyCode) const
    {
        return (IsPressed(keyCode) || IsHeld(keyCode)) ? 1 : 0;
    }

    virtual EKeyState GetState(int32_t keyCode) const = 0;
    virtual bool IsPressed(int32_t keyCode) const = 0;
    virtual bool IsHeld(int32_t keyCode) const = 0;
    virtual bool IsReleased(int32_t keyCode) const = 0;

  protected:
    KeyInputPlatform()
    {
    }
};

class GNOTE_API MouseInputPlatform
{
  public:
    virtual ~MouseInputPlatform() = default;

    inline int8_t GetValue(int32_t button) const
    {
        return (IsPressed(button) || IsHeld(button)) ? 1 : 0;
    }

    virtual EKeyState GetState(int32_t button) const = 0;
    virtual bool IsPressed(int32_t button) const = 0;
    virtual bool IsHeld(int32_t button) const = 0;
    virtual bool IsReleased(int32_t button) const = 0;

    inline float GetPositionX() const
    {
        return mX;
    }
    inline float GetPositionY() const
    {
        return mY;
    }
    inline float GetOffsetX() const
    {
        return mOffsetX;
    }
    inline float GetOffsetY() const
    {
        return mOffsetY;
    }
    inline float GetScrollX() const
    {
        return mScrollX;
    }
    inline float GetScrollY() const
    {
        return mScrollY;
    }

    inline void SetPosition(float x, float y)
    {
        mX = x;
        mY = y;
    }
    inline void SetPositionX(float x)
    {
        mX = x;
    }
    inline void SetPositionY(float y)
    {
        mY = y;
    }

    inline void SetOffset(float offsetX, float offsetY)
    {
        mOffsetX = offsetX;
        mOffsetY = offsetY;
    }
    inline void SetOffsetX(float offsetX)
    {
        mOffsetX = offsetX;
    }
    inline void SetOffsetY(float offsetY)
    {
        mOffsetY = offsetY;
    }

    inline void SetScroll(float scrollX, float scrollY)
    {
        mScrollX = scrollX;
        mScrollY = scrollY;
    }
    inline void SetScrollX(float scrollX)
    {
        mScrollX = scrollX;
    }
    inline void SetScrollY(float scrollY)
    {
        mScrollY = scrollY;
    }

  protected:
    MouseInputPlatform() {};

  protected:
    float mX, mY;
    float mOffsetX, mOffsetY;
    float mScrollX, mScrollY;
};

struct GNOTE_API InputState
{
    KeyInputPlatform *Keyboard;
    MouseInputPlatform *Mouse;
};

extern KeyInputPlatform *createKeyInput();
extern MouseInputPlatform *createMouseInput();
} // namespace Gnote
