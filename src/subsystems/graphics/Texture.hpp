#pragma once

#include <string_view>
#include <memory>

class Texture
{
public:
    explicit Texture(uint32_t id, uint32_t width, uint32_t height) noexcept;
    ~Texture() noexcept;

    void Bind() const noexcept;

    static std::shared_ptr<Texture> LoadTexture(const std::string_view file);

private:
    static uint32_t loadTextureToGPU(const std::string_view file, uint32_t &width, uint32_t &height) noexcept;

private:
    const uint32_t m_id;
    const uint32_t m_width;
    const uint32_t m_height;
};
