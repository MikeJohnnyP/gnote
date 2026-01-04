#pragma once
#include "pch.h"

namespace Gnote {
enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  MouseMoved,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseScroll,
  KeyPressed,
  KeyReleased,
  KeyTyped
};

#define EVENT_CLASS(type)                                                      \
  inline virtual std::string GetName() const override { return #type; }        \
  inline virtual EventType GetType() const override {                          \
    return GetStaticType();                                                    \
  }                                                                            \
  static EventType GetStaticType() { return EventType::type; }

class GNOTE_API Event {
public:
  virtual ~Event() = default;
  bool Handled = false;
  virtual std::string GetName() const = 0;
  virtual EventType GetType() const = 0;
  virtual std::string ToString() { return GetName(); }

protected:
  Event() = default;

private:
};

template <typename T> using EventCallback = std::function<bool(T &)>;

class GNOTE_API EventDispatcher {
public:
  EventDispatcher(Event &event) : m_event(event) {}

  template <typename T> bool Dispatcher(EventCallback<T> callback) {
    if (m_event.GetType() == T::GetStaticType()) {
      m_event.Handled = callback(*(T *)&m_event);
      return true;
    }
    return false;
  }

private:
  Event &m_event;
};
} // namespace Gnote
