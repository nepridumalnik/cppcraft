#include <Window.hpp>

#include <InputEvents.hpp>
#include <GlApi.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

Window::Window() : m_window{nullptr} {}

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
    InputEvents::Instance().SetCurrentWindow(m_window);
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
    if (InputEvents::Instance().KeyJPressed(GLFW_KEY_ESCAPE))
    {
        return true;
    }

    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}
