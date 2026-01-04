#pragma once

#include "pch.h"
#include "Gnote.h"

class Layer2D : public Gnote::Layer {
public:
  Layer2D(std::string name)
      : Layer(name), m_CameraController(Gnote::OrthographicCameraController(
                         (float)1280 / 720, true, true)) {}
  ~Layer2D() {}
  virtual void OnAttach() override {
    // m_Texture =
    // Gnote::Texture2D::Create("./build/bin/Assets/awesomeface.png");
  }
  virtual void OnDettach() override {}
  virtual void OnUpdate(Gnote::TimeSteps &ts) override {
    m_CameraController.OnUpdate(ts);
    Gnote::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1.0});
    Gnote::RenderCommand::Clear();

    Gnote::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (auto i = 0; i < 10; i++) {
      for (auto y = 0; y < 10; y++) {
        Gnote::Renderer2D::DrawQuad(glm::vec2(0.11f * i, 0.11f * y),
                                    glm::vec2(0.1f),
                                    glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
      }
    }

    // for (auto i = 0; i < 10; i++) {
    //   for (auto y = 0; y < 10; y++) {
    //     Gnote::Renderer2D::DrawQuad(glm::vec2(0.22f * i, 0.11f * y),
    //                                 glm::vec2(0.1f), m_Texture);
    //   }
    // }

    Gnote::Renderer2D::EndScene();
  }
  virtual void OnEvent(Gnote::Event &event) override {
    m_CameraController.OnEvent(event);
  }

private:
  Gnote::Ref<Gnote::Texture2D> m_Texture;
  Gnote::ShaderLibrary m_ShaderLibarry;
  Gnote::OrthographicCameraController m_CameraController;
};
