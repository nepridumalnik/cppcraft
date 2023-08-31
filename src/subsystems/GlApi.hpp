#pragma once

#include <string_view>

class GLFWwindow;

class GlApi
{
public:
    static GlApi &Instance();

    GLFWwindow *CreateWindow(uint32_t width, uint32_t height, const std::string_view title);

private:
    GlApi();
    ~GlApi();

    GlApi(const GlApi &) = delete;
    void operator=(const GlApi &) = delete;
};
