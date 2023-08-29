#include <subsystems/Events.hpp>

#include <GLFW/glfw3.h>

void Events::PollEvents()
{
    glfwPollEvents();
}
