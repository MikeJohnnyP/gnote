#include "OpenGLShader.h"
#include "Core/Logger/Logger.h"
#include "pch.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Gnote
{
OpenGLShader::OpenGLShader(const std::string name, const std::string &vertexPath, const std::string &fragmentPath)
    : m_Name(name)
{
    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // // Send the vertex shader source code to GL
    // // Note that std::string's .c_str is NULL character terminated.
    // const GLchar *source = vertexPath.c_str();
    // glShaderSource(vertexShader, 1, &source, 0);

    // // Compile the vertex shader
    // glCompileShader(vertexShader);

    // GLint isCompiled = 0;
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    // if(isCompiled == GL_FALSE)
    // {
    //     GLint maxLength = 0;
    //     glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    //     // The maxLength includes the NULL character
    //     std::vector<GLchar> infoLog(maxLength);
    //     glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
    //     CORE_LOG_ERROR("COMPILE VERTEX SHADER FAILED");
    //     GNOTE_ASSERT(false, &infoLog[0]);

    //     // We don't need the shader anymore.
    //     glDeleteShader(vertexShader);

    //     // Use the infoLog as you see fit.

    //     // In this simple program, we'll just leave
    //     return;
    // }

    // // Create an empty fragment shader handle
    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // // Send the fragment shader source code to GL
    // // Note that std::string's .c_str is NULL character terminated.
    // source = fragmentPath.c_str();
    // glShaderSource(fragmentShader, 1, &source, 0);

    // // Compile the fragment shader
    // glCompileShader(fragmentShader);

    // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    // if (isCompiled == GL_FALSE)
    // {
    //     GLint maxLength = 0;
    //     glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    //     // The maxLength includes the NULL character
    //     std::vector<GLchar> infoLog(maxLength);
    //     glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
    //     CORE_LOG_ERROR("COMPILE FRAGMENT SHADER FAILED");
    //     GNOTE_ASSERT(false, &infoLog[0]);
    //     // We don't need the shader anymore.
    //     glDeleteShader(fragmentShader);
    //     // Either of them. Don't leak shaders.
    //     glDeleteShader(vertexShader);

    //     // Use the infoLog as you see fit.

    //     // In this simple program, we'll just leave
    //     return;
    // }

    // // Vertex and fragment shaders are successfully compiled.
    // // Now time to link them together into a program.
    // // Get a program object.
    // m_ProgramID = glCreateProgram();

    // // Attach our shaders to our program
    // glAttachShader(m_ProgramID, vertexShader);
    // glAttachShader(m_ProgramID, fragmentShader);

    // // Link our program
    // glLinkProgram(m_ProgramID);

    // // Note the different functions here: glGetProgram* instead of
    // glGetShader*. GLint isLinked = 0; glGetProgramiv(m_ProgramID,
    // GL_LINK_STATUS, (int *)&isLinked); if (isLinked == GL_FALSE)
    // {
    //     GLint maxLength = 0;
    //     glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

    //     // The maxLength includes the NULL character
    //     std::vector<GLchar> infoLog(maxLength);
    //     glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);
    //     CORE_LOG_ERROR("LINK SHADER FAILED");
    //     GNOTE_ASSERT(false, &infoLog[0]);
    //     // We don't need the program anymore.
    //     glDeleteProgram(m_ProgramID);
    //     // Don't leak shaders either.
    //     glDeleteShader(vertexShader);
    //     glDeleteShader(fragmentShader);

    //     // Use the infoLog as you see fit.

    //     // In this simple program, we'll just leave
    //     return;
    // }

    // // Always detach shaders after a successful link.
    // glDetachShader(m_ProgramID, vertexShader);
    // glDetachShader(m_ProgramID, fragmentShader);

    std::unordered_map<uint32_t, std::string> source;
    source[GL_VERTEX_SHADER] = ReadFile(vertexPath);
    source[GL_FRAGMENT_SHADER] = ReadFile(fragmentPath);
    Compile(source);
}

OpenGLShader::OpenGLShader(const std::string &name, const std::string &filePath) : m_Name(name)
{
    std::string wholeFile = ReadFile(filePath);
    std::unordered_map<uint32_t, std::string> pairShader = Pairser(wholeFile);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_ProgramID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_ProgramID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

std::string OpenGLShader::GetName() const
{
    return m_Name;
}

void OpenGLShader::UniformMat4(const std::string &uniformName, const glm::mat4 &value)
{
    int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::UniformVec3(const std::string &uniformName, const glm::vec3 &value)
{
    int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UniformFloat(const std::string &uniformName, const float value)
{
    int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
    glUniform1f(location, value);
}

void OpenGLShader::UniformInt(const std::string &uniformName, const int value)
{
    int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
    glUniform1i(location, value);
}

void OpenGLShader::UniformVec4(const std::string &uniformName, const glm::vec4 &value)
{
    int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
    glUniform4f(location, value.r, value.g, value.b, value.a);
}

std::string OpenGLShader::ReadFile(const std::string &filePath)
{
    std::string result;
    std::ifstream in(filePath, std::ios::in | std::ios::binary);

    if (in)
    {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        CORE_LOG_ERROR("Cannot open file: {0}", filePath);
        in.close();
    }
    return result;
}

std::unordered_map<uint32_t, std::string> OpenGLShader::Pairser(std::string &file)
{
    std::unordered_map<uint32_t, std::string> result;
    const char *typeToken = "#type";
    size_t typeLen = strlen(typeToken);
    size_t pos = file.find(typeToken, 0);
    return result;
}

bool OpenGLShader::Compile(std::unordered_map<uint32_t, std::string> Pairser)
{
    std::array<uint32_t, 2> shaderSourse;
    uint32_t count = 0;
    for (auto &shader : Pairser)
    {
        auto &shaderEnum = shader.first;
        auto &shaderString = shader.second;

        GLuint Shader = glCreateShader(shaderEnum);

        const GLchar *source = shaderString.c_str();
        printf("shader source: %s\n", source);
        glShaderSource(Shader, 1, &source, 0);

        glCompileShader(Shader);

        GLint isCompiled = 0;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);
            CORE_LOG_ERROR("COMPILE VERTEX SHADER FAILED");
            GNOTE_ASSERT(false, &infoLog[0]);

            glDeleteShader(Shader);

            return false;
        }

        shaderSourse[count++] = Shader;
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, shaderSourse[0]);
    glAttachShader(program, shaderSourse[1]);

    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        CORE_LOG_ERROR("LINK SHADER FAILED");
        GNOTE_ASSERT(false, &infoLog[0]);
        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(shaderSourse[0]);
        glDeleteShader(shaderSourse[1]);

        return false;
    }

    glDetachShader(program, shaderSourse[0]);
    glDetachShader(program, shaderSourse[1]);

    m_ProgramID = program;
    return true;
}
} // namespace Gnote
