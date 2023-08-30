#pragma once

#include <string_view>
#include <memory>

class Shader
{
public:
    explicit Shader(size_t id);
    ~Shader();

    void Use();

    static std::shared_ptr<Shader> LoadShader(const std::string_view vShader,
                                              const std::string_view fShader);

private:
    Shader() = delete;
    Shader(const Shader &) = delete;
    void operator=(const Shader &) = delete;

    static size_t compileShader(int shaderType, const std::string_view source);

private:
    const size_t m_id;
};
