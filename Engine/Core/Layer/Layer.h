#pragma once
#include "Core/Event/Event.h"
#include "Core/TimeSteps.h"
#include "pch.h"

namespace Gnote {
class GNOTE_API Layer {
public:
  virtual ~Layer();
  virtual void OnAttach() {}
  virtual void OnDettach() {}
  virtual void OnUpdate(TimeSteps &ts) {}
  virtual void OnEvent(Event &event) {}

protected:
  Layer(const std::string name = "");

private:
  std::string m_DebugName;
};
} // namespace Gnote
