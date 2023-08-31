#include <graphics/Shader.hpp>

#include <GL/glew.h>

#include <string>
#include <stdexcept>

Shader::Shader(uint32_t id) noexcept : m_id{id} {}

Shader::~Shader() noexcept
{
    glDeleteProgram(m_id);
}

void Shader::Use() const noexcept
{
    glUseProgram(m_id);
}

uint32_t Shader::compileShader(int shaderType, const std::string_view source)
{
    int status = -1;
    uint32_t shaderId = glCreateShader(shaderType);
    const GLchar *sourcePtr = source.data();

    glShaderSource(shaderId, 1, &sourcePtr, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        std::string error;
        error.resize(512);

        glGetShaderInfoLog(shaderId, error.size(), nullptr, &error[0]);
        glDeleteShader(shaderId);

        throw std::runtime_error{std::move(error)};
    }

    return shaderId;
}

std::shared_ptr<Shader> Shader::LoadShader(const std::string_view vShader,
                                           const std::string_view fShader)
{
    int status = -1;
    const uint32_t vertexId = compileShader(GL_VERTEX_SHADER, vShader);
    const uint32_t fragmentId = compileShader(GL_FRAGMENT_SHADER, fShader);
    const uint32_t programId = glCreateProgram();

    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &status);

    if (!status)
    {
        std::string error;
        error.resize(512);

        glGetProgramInfoLog(programId, error.size(), nullptr, &error[0]);
        glDeleteProgram(programId);

        throw std::runtime_error{std::move(error)};
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return std::make_shared<Shader>(programId);
}
