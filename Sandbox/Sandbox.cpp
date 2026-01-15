#include "Gnote.h"
#include "Layer2D.h"

class SandBox : public Gnote::Application
{
  public:
    SandBox() : m_Layer2D(new Layer2D("Layer2D")) {};
    bool ClientInit() override
    {
        PushLayer(m_Layer2D);
        std::cout << "Sandbox Init" << std::endl;
        return true;
    }

    bool ClientShutdown() override
    {
        return true;
    }

  private:
    Layer2D *m_Layer2D;
};

Gnote::Application *Gnote::createApplication()
{
    return new SandBox();
}

Gnote::WindowSpec Gnote::createSpec()
{
    Gnote::WindowSpec spec;
    spec.width = 1280;
    spec.height = 720;
    spec.Title = "My window";
    spec.Vsync = true;
    return spec;
}
