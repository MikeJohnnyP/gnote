#pragma once
#include "Core/Event/Event.h"

namespace Gnote {
class GNOTE_API KeyEvent : public Event {
public:
  virtual ~KeyEvent() = default;
  inline int GetKeyCode() { return keyCode; }
  inline virtual std::string ToString() override {
    std::stringstream ss;
    ss << "KeyCode: " << keyCode;
    return ss.str();
  }

protected:
  KeyEvent(int keyCode) : keyCode(keyCode) {}
  int keyCode;
};

class GNOTE_API KeyPressed : public KeyEvent {
public:
  KeyPressed(int keyCode, int repeat_count)
      : KeyEvent(keyCode), repeat_count(repeat_count) {}
  EVENT_CLASS(KeyPressed);
  inline virtual std::string ToString() override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << "(" << keyCode << ", " << repeat_count << ")";
    return ss.str();
  }

private:
  int repeat_count;
};

class GNOTE_API KeyReleased : public KeyEvent {
public:
  KeyReleased(int keyCode) : KeyEvent(keyCode) {}
  inline virtual std::string ToString() override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << "(" << keyCode << ")";
    return ss.str();
  }
  EVENT_CLASS(KeyReleased);

private:
};

class GNOTE_API KeyTyped : public KeyEvent {
public:
  KeyTyped(int keyCode) : KeyEvent(keyCode) {}
  inline virtual std::string ToString() override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << "(" << (char)keyCode << ")";
    return ss.str();
  }
  EVENT_CLASS(KeyTyped);

private:
};
} // namespace Gnote
