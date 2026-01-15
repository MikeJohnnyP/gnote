#pragma once
#include "pch.h"
#include "Core/Layer/Layer.h"

namespace Gnote
{
class GNOTE_API ImGuiLayer : public Layer
{
  public:
    ImGuiLayer(std::string name = "ImGuiLayer");
    virtual ~ImGuiLayer() override;

    virtual void OnAttach() override;
    virtual void OnDettach() override;
    virtual void OnUpdate(TimeSteps &ts) override;
    virtual void OnEvent(Event &event) override;

    virtual void Begin();
    virtual void End();

  private:
};
} // namespace Gnote
