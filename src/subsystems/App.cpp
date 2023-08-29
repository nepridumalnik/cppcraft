#include <subsystems/App.hpp>

#include <subsystems/Window.hpp>

#include <stdexcept>

void App::Run()
{
    Window window;
    window.Initialize(m_defaultWidth, m_defaultHeight, "CppCraft");

    while (!window.ShouldClose())
    {
        window.SwapBuffers();
    }
}