// #include "Gnote.h"
// #include "Layer2D.h"

// class SandBox : public Gnote::Application
// {
//   public:
//     SandBox() : m_Layer2D(new Layer2D("Layer2D")) {};
//     bool ClientInit() override
//     {
//         PushLayer(m_Layer2D);
//         LOG_INFO("Sandbox init {0}", 1);
//         return true;
//     }
//
//     bool ClientShutdown() override
//     {
//         return true;
//     }
//
//   private:
//     Layer2D *m_Layer2D;
// };
//
// Gnote::Application *Gnote::createApplication()
// {
//     return new SandBox();
// }
//
// Gnote::WindowSpec Gnote::createSpec()
// {
//     Gnote::WindowSpec spec;
//     spec.width = 1280;
//     spec.height = 720;
//     spec.Title = "My window";
//     spec.Vsync = true;
//     return spec;
// }

#include <memory>
#include "Core/Window.h"
#include "Core/Platform/Windows/Win32Windows.h"

int main()
{
    Gnote::WindowSpec spec = {1280, 720, "Hello", true};
    std::unique_ptr<Gnote::Window> window = std::make_unique<Gnote::Win32Windows>(spec);
    window->Init();
    while (window->IsWindowClose())
    {
        window->PollEvent();
    }

    window->Shutdown();
    return 0;
}
