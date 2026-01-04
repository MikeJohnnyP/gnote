#include "Core/Renderer/GraphicsContext.h"
#include "Core/Renderer/Shader.h"
#include "Core/Window.h"

struct GLFWwindow;
namespace Gnote
{
class WindowsWindow : public Window
{
  public:
    WindowsWindow(WindowSpec &spec);
    ~WindowsWindow() = default;
    virtual bool Init() override;
    virtual void Shutdown() override;
    virtual void SwapBuffer() override;
    virtual void PollEvent() override;
    virtual bool IsWindowClose() override;
    virtual bool IsVsyncEnable() override;
    virtual void SetFunctionCallback(const EventFn &callback) override;
    virtual void *GetNativeWindow() override;
    virtual float GetTime() override;
    virtual float GetTimeMiliSeconds() override;
    virtual InputState *GetInputState() override;

  protected:
  private:
    GLFWwindow *m_GLFWwindow;
    GraphicsContext *m_context;

    struct WindowData
    {
        unsigned int width, height;
        std::string Title;
        bool vSync;
        InputState inputState;
        EventFn callback;
    };

    WindowData m_data;
};
} // namespace Gnote
