#include <graphics/Texture.hpp>

#include <GL/glew.h>

#include <png.h>

#include <vector>
#include <stdexcept>

Texture::Texture(uint32_t id, uint32_t width, uint32_t height) noexcept
    : m_id{id},
      m_width{width},
      m_height{height}
{
}

Texture::~Texture() noexcept
{
    glDeleteTextures(1, &m_id);
}

void Texture::Bind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

std::shared_ptr<Texture> Texture::LoadTexture(const std::string_view file)
{
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t textureId = loadTextureToGPU(file, width, height);

    if (textureId == 0)
    {
        throw std::runtime_error{std::string{"Failed to load texture from file: "} + file.data()};
    }

    return std::make_shared<Texture>(textureId, width, height);
}

// Честно украдено
// Не менять
uint32_t Texture::loadTextureToGPU(const std::string_view file, uint32_t &width, uint32_t &height) noexcept
{
    std::unique_ptr<FILE, decltype(&fclose)> fileAutoCloser{nullptr, nullptr};
    FILE *f = nullptr;

    int isPng = -1;
    int bDepth = -1;
    int colorType = -1;
    int rowBytes = -1;
    int alpha = -1;

    png_infop infoPtr = nullptr;
    png_infop endInfo = nullptr;
    png_structp pngPtr = nullptr;

    png_uint_32 tWidth = 0;
    png_uint_32 tHeight = 0;

    png_byte header[8]{};

    std::vector<png_byte> imageData;
    std::vector<png_byte *> rowPointers;

    uint32_t texture = 0;

    if (!(f = fopen(file.data(), "rb")))
    {
        return 0;
    }

    fileAutoCloser = std::unique_ptr<FILE, decltype(&fclose)>(f, fclose);

    fread(header, 1, 8, f);
    isPng = !png_sig_cmp(header, 0, 8);

    if (!isPng)
    {
        return 0;
    }

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (!pngPtr)
    {
        return 0;
    }

    infoPtr = png_create_info_struct(pngPtr);

    if (!infoPtr)
    {
        png_destroy_read_struct(&pngPtr, nullptr, nullptr);
        return 0;
    }

    endInfo = png_create_info_struct(pngPtr);

    if (!endInfo)
    {
        png_destroy_read_struct(&pngPtr, nullptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        return 0;
    }

    png_init_io(pngPtr, f);
    png_set_sig_bytes(pngPtr, 8);
    png_read_info(pngPtr, infoPtr);
    png_get_IHDR(pngPtr, infoPtr, &tWidth, &tHeight, &bDepth, &colorType, nullptr, nullptr, nullptr);
    width = tWidth;
    height = tHeight;
    png_read_update_info(pngPtr, infoPtr);
    rowBytes = png_get_rowbytes(pngPtr, infoPtr);

    imageData.resize(rowBytes * tHeight * sizeof(png_byte));
    rowPointers.resize(tHeight * sizeof(png_bytep));

    for (unsigned int i = 0; i < tHeight; ++i)
    {
        rowPointers[tHeight - 1 - i] = &imageData[i * rowBytes];
    }

    png_read_image(pngPtr, rowPointers.data());

    switch (png_get_color_type(pngPtr, infoPtr))
    {
    case PNG_COLOR_TYPE_RGBA:
        alpha = GL_RGBA;
        break;

    case PNG_COLOR_TYPE_RGB:
        alpha = GL_RGB;
        break;

    default:
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tWidth, tHeight, 0, alpha, GL_UNSIGNED_BYTE, imageData.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);

    return texture;
}
