#include "Renderer2D.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "pch.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Gnote
{
struct Renderer2DStorage
{
    Ref<Texture2D> whiteTexture;
    Ref<VertexArray> VAO;
    Ref<Shader> shader2D;
};

static Renderer2DStorage *rendererData;
void Renderer2D::Init()
{
    rendererData = new Renderer2DStorage();
    float data[] = {
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // bottom right
    };
    Ref<VertexBuffer> m_VBO = VertexBuffer::create(data, sizeof(data));
    BufferLayout m_Layout = {{ShaderDataType::Float3, "a_Pos"}, {ShaderDataType::Float2, "a_TextCord"}};
    m_VBO->SetLayout(m_Layout);

    uint32_t indicies[] = {0, 1, 2, 2, 3, 1};
    Ref<IndexBuffer> m_EBO = IndexBuffer::create(indicies, sizeof(indicies));

    rendererData->VAO = VertexArray::Create();
    rendererData->VAO->AddVertexBuffer(m_VBO);
    rendererData->VAO->SetIndexBuffer(m_EBO);

    rendererData->shader2D =
        Shader::create("Shader", "./build/bin/DefaultShader/Vertex.glsl", "./build/bin/DefaultShader/Fragment.glsl");
    rendererData->shader2D->Bind();
    rendererData->shader2D->SetInt("u_Texture", 0);

    rendererData->whiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteData = 0xffffffff;
    rendererData->whiteTexture->SetData(&whiteData, sizeof(uint32_t));
}

void Renderer2D::Shudown()
{
    rendererData->shader2D->Unbind();
    rendererData->VAO->Unbind();
    rendererData->whiteTexture->Unbind();
    delete rendererData;
}

void Renderer2D::Resizing(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}
void Renderer2D::BeginScene(const Camera &camera)
{
    rendererData->shader2D->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}
void Renderer2D::EndScene()
{
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
{
    rendererData->shader2D->Bind();
    rendererData->shader2D->SetVec4("u_Color", glm::vec4(1.0f));
    texture->Bind();

    rendererData->VAO->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0});

    rendererData->shader2D->SetMat4("u_ModelMatrix", model);

    RenderCommand::DrawIndexed(rendererData->VAO);
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
{
    DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
{
    rendererData->shader2D->Bind();
    rendererData->whiteTexture->Bind();

    rendererData->VAO->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0});

    rendererData->shader2D->SetMat4("u_ModelMatrix", model);
    rendererData->shader2D->SetVec4("u_Color", color);

    RenderCommand::DrawIndexed(rendererData->VAO);
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
{
    DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
}
} // namespace Gnote
