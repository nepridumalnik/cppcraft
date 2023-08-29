#include <subsystems/Window.hpp>

#include <stdexcept>
#include <iostream>

static constexpr int Width = 800;
static constexpr int Height = 600;

int main(int argc, char const *argv[])
{
    try
    {
        Window window;
        window.Initialize(Width, Height, "CppCraft");

        while (!window.ShouldClose())
        {
            window.SwapBuffers();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
