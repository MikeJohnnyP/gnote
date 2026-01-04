#pragma once
#include "pch.h"

namespace Gnote
{
class GNOTE_API GraphicsContext
{
  public:
    virtual void Init() {};
    virtual void SwapBuffer() {};

  protected:
    GraphicsContext()
    {
    }
    virtual ~GraphicsContext()
    {
    }
};
} // namespace Gnote
