#include <subsystems/Window.hpp>

#include <subsystems/GlApi.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

Window::Window() : m_window{nullptr} {}

Window::~Window()
{
    Terminate();
}

void Window::Initialize(size_t width, size_t height, const std::string_view title)
{
    if (m_window)
    {
        return;
    }

    GlApi &api = GlApi::Instance();
    m_window = api.CreateWindow(width, height, title);
}

void Window::Terminate()
{
    if (!m_window)
    {
        return;
    }

    glfwDestroyWindow(m_window);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    m_event.PollEvents();
    glfwSwapBuffers(m_window);
}
