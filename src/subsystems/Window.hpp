#pragma once

#include <subsystems/InputEvents.hpp>

#include <string_view>

class GLFWwindow;

class Window
{
public:
    Window();
    ~Window();

    void Initialize(size_t width, size_t height, const std::string_view title);
    void Terminate();
    bool ShouldClose();
    void SwapBuffers();

private:
    Window(const Window &) = delete;
    void operator=(const Window &) = delete;

private:
    GLFWwindow *m_window;
    InputEvents &m_inputEvent;
};
