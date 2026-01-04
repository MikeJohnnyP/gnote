#pragma once

#include "Gnote.h"
#include "pch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Platform/OpenGL/OpenGLShader.h"
#include "Core/Renderer/Camera/PerspectiveCamera.h"

class GameLayer : public Gnote::Layer
{
  public:
    GameLayer(std::string name)
        : Layer(name), m_CameraController(Gnote::OrthographicCameraController(1280 / 720, true, true)),
          m_PerspectiveCamera(Gnote::PerspectiveCamera(glm::vec3(0.0f, 0.0f, -10.0f), 1280 / 720))
    {
    }

    virtual void OnAttach() override
    {

        Gnote::Ref<Gnote::Shader> m_Shader = m_ShaderLibarry.Load(
            "Shader", "./build/bin/Assets/Shader/VertexShader.glsl", "./build/bin/Assets/Shader/FragmentShader.glsl");

        m_VertexArray = Gnote::VertexArray::Create();

        float vertices[4 * 5] = {
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // bottom right
        };

        float cube[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
            0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

            -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
            0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

        // Gnote::Ref<Gnote::VertexBuffer> m_VBO;
        // m_VBO = Gnote::VertexBuffer::create(vertices, sizeof(vertices));

        // Gnote::BufferLayout layout({{Gnote::ShaderDataType::Float3, "aPos"},
        // {Gnote::ShaderDataType::Float2, "aTextureNormal"}});
        // m_VBO->SetLayout(layout);

        // m_VertexArray->AddVertexBuffer(m_VBO);

        // uint32_t indices[6] = { 0, 1, 2, 2, 3, 1 };
        // Gnote::Ref<Gnote::IndexBuffer> m_EBO;
        // m_EBO = Gnote::IndexBuffer::create(indices, sizeof(indices));
        // m_VertexArray->SetIndexBuffer(m_EBO);

        Gnote::Ref<Gnote::VertexBuffer> m_CubeVBO;
        m_CubeVBO = Gnote::VertexBuffer::create(cube, sizeof(cube));

        Gnote::BufferLayout cubeLayout(
            {{Gnote::ShaderDataType::Float3, "aPos"}, {Gnote::ShaderDataType::Float2, "aTextureNormal"}});
        m_CubeVBO->SetLayout(cubeLayout);

        m_VertexArray->AddVertexBuffer(m_CubeVBO);

        m_texture1 = Gnote::Texture2D::Create("./build/bin/Assets/container.jpg");

        m_texture2 = Gnote::Texture2D::Create("./build/bin/Assets/awesomeface.png");

        DYNAMIC_CAST(m_Shader, Gnote::OpenGLShader)->Bind();
        DYNAMIC_CAST(m_Shader, Gnote::OpenGLShader)->UniformInt("u_Texture", 0);
    }

    virtual void OnUpdate(Gnote::TimeSteps &ts) override
    {
        m_CameraController.OnUpdate(ts);
        Gnote::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Gnote::RenderCommand::Clear();
        Gnote::Ref<Gnote::Shader> getShader = m_ShaderLibarry.Get("Shader");
        Gnote::Renderer::BeginScene(m_CameraController.GetCamera(), {{getShader}});

        // m_texture1->Bind();
        Gnote::Renderer::Submit(m_VertexArray, getShader);

        // Gnote::Renderer::Submit(m_VertexArray, m_Shader);

        // for(int i = 0; i < 20; i++)
        // {
        //     for(int y = 0; y < 20; y++)
        //     {
        //         glm::vec3 position = {i * 0.11f, y * 0.11f, 0.11f};
        //         glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
        //                           * glm::scale(glm::mat4(1.0f), {0.1f, 0.1f,
        //                           0.1f});
        //         m_texture2->Bind();

        //         Gnote::Renderer::Submit(m_VertexArray, m_Shader, model);
        //     }
        // }
        // m_texture2->Bind();
        // Gnote::Renderer::Submit(m_VertexArray, getShader);
        Gnote::Renderer::EndScene();
    }

    virtual void OnEvent(Gnote::Event &event) override
    {
        Gnote::EventDispatcher dispatcher(event);
        dispatcher.Dispatcher<Gnote::MouseButtonPressed>(GNOTE_EVENT_BIND(GameLayer::OnMousePressed));
        m_CameraController.OnEvent(event);
    }

    bool OnMousePressed(Gnote::MouseButtonPressed &event)
    {
        return false;
    }

  private:
    Gnote::Ref<Gnote::VertexArray> m_VertexArray;
    Gnote::Ref<Gnote::Texture2D> m_texture1;
    Gnote::Ref<Gnote::Texture2D> m_texture2;
    Gnote::ShaderLibrary m_ShaderLibarry;
    Gnote::OrthographicCameraController m_CameraController;
    Gnote::PerspectiveCamera m_PerspectiveCamera;
};
