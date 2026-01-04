#include "Application.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"
#include "Core/TimeSteps.h"
#include "Input.h"
#include "Logger/Logger.h"
#include "pch.h"
#include <glad/glad.h>

namespace Gnote {
Application *Application::s_instance = nullptr;

bool Application::Init() {
  if (s_instance == nullptr) {
    s_instance = this;
  }
  Logger::Init();
  CORE_LOG_INFO("Application Init Succesfully");

  m_window = createWindow();

  if (!m_window->Init()) {
    return false;
  }

  // Renderer::Init();
  Renderer2D::Init();

  ClientInit();
  m_window->SetFunctionCallback(GNOTE_EVENT_BIND(Application::OnEvent));
  m_isWindowClose = m_window->IsWindowClose();

  m_inputState = m_window->GetInputState();

  /*
      Hardware Info
  */
  CORE_LOG_INFO("Vendor: {0}", (const char *)glGetString(GL_VENDOR));
  CORE_LOG_INFO("Renderer: {0}", (const char *)glGetString(GL_RENDERER));
  CORE_LOG_INFO("Version: {0}", (const char *)glGetString(GL_VERSION));
  CORE_LOG_INFO("Shading Language: {0}",
                (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

  return true;
}

void Application::Run() {
  float currentTime;
  float lastTime = 0;

  while (!m_isWindowClose && !m_window->IsWindowClose()) {
    currentTime = m_window->GetTime();
    TimeSteps ts = currentTime - lastTime;

    m_window->SwapBuffer();
    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate(ts);
    }
    m_window->PollEvent();

    lastTime = currentTime;
  }
}

void Application::Shutdown() { ClientShutdown(); }

void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatcher<KeyPressed>(GNOTE_EVENT_BIND(Application::WindowClose));
  dispatcher.Dispatcher<WindowResizeEvent>(
      GNOTE_EVENT_BIND(Application::WindowResize));
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(event);
    if (event.Handled)
      break;
  }
}

void Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

void Application::PopLayer(Layer *layer) {
  m_LayerStack.PopLayer(layer);
  layer->OnDettach();
}

void Application::PopOverlay(Layer *overlay) {
  m_LayerStack.PopOverlay(overlay);
  overlay->OnDettach();
}

Window *Application::GetWindow() { return m_window; }

Application *Application::GetInstance() { return s_instance; }

Application::~Application() {}
bool Application::WindowClose(KeyPressed &event) {
  if (m_inputState->Keyboard->IsPressed(GNOTE_KEY_ESCAPE)) {
    m_isWindowClose = true;
  }
  return true;
}

bool Application::WindowResize(WindowResizeEvent &event) {
  Renderer::Resizing(event.GetWidth(), event.GetHeight());
  return false;
}
} // namespace Gnote
