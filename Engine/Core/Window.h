#pragma once
#include "Core/Event/Event.h"
#include "InputPlatform.h"
#include "pch.h"

namespace Gnote {
struct WindowSpec {
  unsigned int width, height;
  std::string Title;

  bool Vsync = false;
};

class GNOTE_API Window {
public:
  using EventFn = std::function<void(Event &)>;
  virtual ~Window() = default;
  virtual bool Init() = 0;
  virtual void Shutdown() = 0;
  virtual void SwapBuffer() = 0;
  virtual void PollEvent() = 0;
  virtual bool IsWindowClose() = 0;
  virtual bool IsVsyncEnable() = 0;
  virtual void SetFunctionCallback(const EventFn &callback) = 0;
  virtual void *GetNativeWindow() = 0;
  virtual float GetTime() = 0;
  virtual float GetTimeMiliSeconds() = 0;
  virtual InputState *GetInputState() = 0;

protected:
  Window() = default;
};
extern Window *createWindow();
WindowSpec createSpec();
} // namespace Gnote
