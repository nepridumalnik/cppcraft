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

uint32_t Texture::loadTextureToGPU(const std::string_view file, uint32_t &width, uint32_t &height) noexcept
{
    struct PngDeleter
    {
        PngDeleter() : pngPtr{nullptr}, infoPtr{nullptr}, endInfo{nullptr} {}
        ~PngDeleter() { png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo); }

        png_structp pngPtr;
        png_infop infoPtr;
        png_infop endInfo;
    };

    int isPng = -1;
    int bDepth = -1;
    int colorType = -1;
    int rowBytes = -1;
    int alpha = -1;

    // ID текстуры в видеопамяти
    uint32_t texture = 0;

    png_uint_32 tWidth = 0;
    png_uint_32 tHeight = 0;

    // Заголовок PNG формата
    png_byte header[8];

    // Данные изображения
    std::vector<png_byte> imageData;
    std::vector<png_byte *> rowPointers;

    // Автоудалитель данных PNG структур
    PngDeleter pngDeleter;

    // Умный указатель на файл
    std::unique_ptr<FILE, decltype(&fclose)> filePtr{nullptr, nullptr};

    {
        FILE *f = nullptr;

        if (!(f = fopen(file.data(), "rb")))
        {
            return 0;
        }

        filePtr = std::unique_ptr<FILE, decltype(&fclose)>(f, fclose);
    }

    fread(header, 1, 8, filePtr.get());
    isPng = !png_sig_cmp(header, 0, 8);

    if (!isPng)
    {
        return 0;
    }

    pngDeleter.pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (!pngDeleter.pngPtr)
    {
        return 0;
    }

    pngDeleter.infoPtr = png_create_info_struct(pngDeleter.pngPtr);

    if (!pngDeleter.infoPtr)
    {
        return 0;
    }

    pngDeleter.endInfo = png_create_info_struct(pngDeleter.pngPtr);

    if (!pngDeleter.endInfo)
    {
        return 0;
    }

    if (setjmp(png_jmpbuf(pngDeleter.pngPtr)))
    {
        return 0;
    }

    png_init_io(pngDeleter.pngPtr, filePtr.get());
    png_set_sig_bytes(pngDeleter.pngPtr, 8);
    png_read_info(pngDeleter.pngPtr, pngDeleter.infoPtr);
    png_get_IHDR(pngDeleter.pngPtr, pngDeleter.infoPtr, &tWidth, &tHeight, &bDepth, &colorType, nullptr, nullptr, nullptr);
    width = tWidth;
    height = tHeight;
    png_read_update_info(pngDeleter.pngPtr, pngDeleter.infoPtr);
    rowBytes = png_get_rowbytes(pngDeleter.pngPtr, pngDeleter.infoPtr);

    imageData.resize(rowBytes * tHeight * sizeof(png_byte));
    rowPointers.resize(tHeight * sizeof(png_bytep));

    for (unsigned int i = 0; i < tHeight; ++i)
    {
        rowPointers[tHeight - 1 - i] = &imageData[i * rowBytes];
    }

    png_read_image(pngDeleter.pngPtr, rowPointers.data());

    switch (png_get_color_type(pngDeleter.pngPtr, pngDeleter.infoPtr))
    {
    case PNG_COLOR_TYPE_RGBA:
        alpha = GL_RGBA;
        break;

    case PNG_COLOR_TYPE_RGB:
        alpha = GL_RGB;
        break;

    default:
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tWidth, tHeight, 0, alpha, GL_UNSIGNED_BYTE, imageData.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
