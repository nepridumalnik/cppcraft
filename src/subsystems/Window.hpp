#pragma once

#include <subsystems/Events.hpp>

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
    GLFWwindow *m_window;
    Events m_event;
};
