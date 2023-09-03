#include <Window.hpp>

#include <InputEvents.hpp>
#include <GlApi.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

Window::Window() : m_window{nullptr}, m_cursorLocked{true}{}

Window::~Window()
{
    Terminate();
}

void Window::Initialize(uint32_t width, uint32_t height, const std::string_view title)
{
    if (m_window)
    {
        return;
    }

    GlApi &api = GlApi::Instance();

    m_window = api.CreateWindow(width, height, title);
    m_width = width;
    m_height = height;

    InputEvents::Instance().SetCurrentWindow(m_window);

    setCursorVisible(m_cursorLocked);
}

void Window::Terminate() noexcept
{
    if (!m_window)
    {
        return;
    }

    glfwDestroyWindow(m_window);
}

bool Window::ShouldClose() const noexcept
{
    if (InputEvents::Instance().KeyJPressed(GLFW_KEY_ESCAPE))
    {
        return true;
    }

    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers() const noexcept
{
    glfwSwapBuffers(m_window);
}

void Window::ToggleCursor() noexcept
{
    m_cursorLocked = !m_cursorLocked;
    setCursorVisible(m_cursorLocked);
}

void Window::setCursorVisible(bool flag) noexcept
{
    glfwSetInputMode(m_window, GLFW_CURSOR, flag ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
