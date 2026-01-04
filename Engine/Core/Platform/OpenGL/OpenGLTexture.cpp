#include "OpenGLTexture.h"
#include "Core/Logger/Logger.h"
#include <stb_image.h>
#include <glad/glad.h>

namespace Gnote
{
OpenGLTexture::OpenGLTexture(const std::string &filePath) : m_Width(0), m_Height(0), m_Channels(0), m_Data(nullptr)
{
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    if (!data)
    {
        CORE_LOG_ERROR("stb_image error: %s", stbi_failure_reason());
    }
    GNOTE_ASSERT(data, "Failed to load image!");
    GLenum internalFormat = 0, dataFormat = 0;
    if (m_Channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (m_Channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;

    GNOTE_ASSERT(internalFormat & dataFormat, "Format not supported!");

    // OpenGL 4.5
    // glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    // glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);
    // glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat,
    //                     GL_UNSIGNED_BYTE, data);

    // OpenGL 3.3
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height), m_Channels(0), m_Data(nullptr)
{
    m_InternalFormat = GL_RGBA8;
    m_DataFormat = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);
    glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void OpenGLTexture::SetData(void *data, uint32_t size)
{
    // OpenGL 4.5
    // uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    // GNOTE_ASSERT(size == m_Width * m_Height * bpp,
    //              "Data must be entire texture!");
    // glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat,
    //                     GL_UNSIGNED_BYTE, data);

    // OpenGL 3.3
    uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    GNOTE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
    glBindTexture(GL_TEXTURE_2D, m_TextureID); // Bind texture trước
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind sau khi upload (tùy chọn)
}

void OpenGLTexture::Bind(uint32_t slot) const
{
    // OpenGL 4.5
    // glBindTextureUnit(slot, m_TextureID);
    // OpenGL 3.3
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void OpenGLTexture::Unbind() const
{
    // OpenGL 4.5
    //  glBindTextureUnit(0, m_TextureID);
    glBindTexture(GL_TEXTURE_2D, 0);
}
} // namespace Gnote
