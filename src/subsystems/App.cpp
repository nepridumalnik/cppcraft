#include <App.hpp>

#include <Window.hpp>

#include <graphics/Shader.hpp>

#include <generated/shaders.hpp>

#include <stdexcept>

void App::Run()
{
    Window window;
    window.Initialize(m_defaultWidth, m_defaultHeight, "CppCraft");

    auto shader = Shader::LoadShader(MainVert, MainFrag);

    while (!window.ShouldClose())
    {
        window.SwapBuffers();
    }
}
