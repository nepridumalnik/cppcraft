#include <graphics/Shader.hpp>

#include <GL/glew.h>

#include <string>
#include <stdexcept>

Shader::Shader(size_t id) : m_id{id} {}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::Use()
{
}

size_t Shader::compileShader(int shaderType, const std::string_view source)
{
    int status = -1;
    size_t shaderId = glCreateShader(shaderType);
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
    const size_t vertexId = compileShader(GL_VERTEX_SHADER, vShader);
    const size_t fragmentId = compileShader(GL_FRAGMENT_SHADER, fShader);
    const size_t programId = glCreateProgram();

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
