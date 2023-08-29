#pragma once

#include <string_view>

class GLFWwindow;

class GlApi
{
public:
    static GlApi &Instance();

    GLFWwindow *CreateWindow(size_t width, size_t height, const std::string_view title);

private:
    GlApi();
    ~GlApi();

    GlApi(const GlApi &) = delete;
    void operator=(const GlApi &) = delete;
};
