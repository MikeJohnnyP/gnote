#include "OpenGLBuffer.h"
#include "pch.h"
#include <glad/glad.h>

namespace Gnote
{
// OpenGL Vertex Buffer
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertex, uint32_t size)
{
    m_Count = size / sizeof(float);
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_VBO);
}
void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}
void OpenGLVertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t OpenGLVertexBuffer::GetCount()
{
    return m_Count;
}

// OpenGL Index Buffer
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indicies, uint32_t count)
{
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indicies, GL_STATIC_DRAW);
    m_Count = count;
}
OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_EBO);
}
void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}
void OpenGLIndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
uint32_t OpenGLIndexBuffer::GetCount()
{
    return m_Count;
}
} // namespace Gnote
