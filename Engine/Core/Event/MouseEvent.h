#pragma once

#include "Event.h"

namespace Gnote
{
class GNOTE_API MouseMoved : public Event
{
  public:
    MouseMoved(float x_pos, float y_pos) : x_pos(x_pos), y_pos(y_pos)
    {
    }
    inline virtual std::string ToString() override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << "(" << x_pos << ", " << y_pos << ")";
        return ss.str();
    }
    EVENT_CLASS(MouseMoved);

  private:
    float x_pos, y_pos;
};

class GNOTE_API MouseButtonEvent : public Event
{
  public:
    virtual ~MouseButtonEvent() = default;

  protected:
    MouseButtonEvent(int button) : button(button)
    {
    }
    int button;
};

class GNOTE_API MouseButtonPressed : public MouseButtonEvent
{
  public:
    MouseButtonPressed(int button) : MouseButtonEvent(button)
    {
    }
    inline virtual std::string ToString() override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << button;
        return ss.str();
    }
    EVENT_CLASS(MouseButtonPressed);

  private:
};

class GNOTE_API MouseButtonReleased : public MouseButtonEvent
{
  public:
    MouseButtonReleased(int button) : MouseButtonEvent(button)
    {
    }
    inline virtual std::string ToString() override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << button;
        return ss.str();
    }
    EVENT_CLASS(MouseButtonReleased);

  private:
};

class GNOTE_API MouseScroll : public Event
{
  public:
    MouseScroll(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset)
    {
    }
    inline virtual std::string ToString() override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << "(" << xOffset << ", " << yOffset << ")";
        return ss.str();
    }

    EVENT_CLASS(MouseScroll);

  private:
    float xOffset, yOffset;
};
} // namespace Gnote
