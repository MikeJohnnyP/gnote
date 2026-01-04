#pragma once

extern Gnote::Application *Gnote::createApplication();

int main()
{
    auto app = Gnote::createApplication();
    if (app->Init())
    {
        app->Run();
    }

    app->Shutdown();
    delete app;
}
