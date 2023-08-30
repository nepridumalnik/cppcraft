#include <Window.hpp>

#include <GlApi.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

Window::Window() : m_window{nullptr}, m_inputEvent{InputEvents::Instance()} {}

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
    m_inputEvent.SetCurrentWindow(m_window);
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
    if (m_inputEvent.KeyJPressed(GLFW_KEY_ESCAPE))
    {
        return true;
    }

    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    m_inputEvent.PollEvents();
    glfwSwapBuffers(m_window);
}
