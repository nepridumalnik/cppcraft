#pragma once

#include <string_view>
#include <memory>

class Shader
{
public:
    explicit Shader(uint32_t id) noexcept;
    ~Shader() noexcept;

    void Use() const noexcept;

    static std::shared_ptr<Shader> LoadShader(const std::string_view vShader,
                                              const std::string_view fShader);

private:
    Shader() = delete;
    Shader(const Shader &) = delete;
    void operator=(const Shader &) = delete;

    static uint32_t compileShader(int shaderType, const std::string_view source);

private:
    const uint32_t m_id;
};
