#include <imgui.h>

#include "ImGuiLayer.h"
#include "Core/Application.h"

namespace Gnote
{
ImGuiLayer::ImGuiLayer(std::string name) : Layer(name)
{
}
ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnAttach()
{
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO();
    // (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //
    // ImGui::StyleColorsDark();
    //
    // const float main_scale = Application::GetInstance()->GetWindow()->GetMainScale();
    //
    // ImGuiStyle &style = ImGui::GetStyle();
    // style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for
    //                                  // dynamic style scaling, changing this requires resetting
    //                                  // Style + calling this again)
    // style.FontScaleDpi = main_scale; // Set initial font scale. (using io.ConfigDpiScaleFonts=true
    //                                  // makes this unnecessary. We leave both here for
    //                                  // documentation purpose)
}
void ImGuiLayer::OnDettach()
{
}
void ImGuiLayer::OnUpdate(TimeSteps &ts)
{
}
void ImGuiLayer::OnEvent(Event &event)
{
}

void ImGuiLayer::Begin()
{
}
void ImGuiLayer::End()
{
}

} // namespace Gnote
