#pragma once

#include <string_view>

class GLFWwindow;

class Window
{
public:
    Window();
    ~Window();

    void Initialize(uint32_t width, uint32_t height, const std::string_view title);
    void Terminate() noexcept;
    bool ShouldClose() const noexcept;
    void SwapBuffers() const noexcept;
    void ToggleCursor() noexcept;

private:
    void setCursorVisible(bool flag) noexcept;

    Window(const Window &) = delete;
    void operator=(const Window &) = delete;

private:
    GLFWwindow *m_window;

    uint32_t m_width;
    uint32_t m_height;

    bool m_cursorLocked;
};
