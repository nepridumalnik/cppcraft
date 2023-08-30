#include <InputEvents.hpp>

#include <GLFW/glfw3.h>

InputEvents &InputEvents::Instance()
{
    static InputEvents events;
    return events;
}

void InputEvents::SetCurrentWindow(GLFWwindow *window)
{
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
}

void InputEvents::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    InputEvents &events = Instance();
}

void InputEvents::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    InputEvents &events = Instance();
}

void InputEvents::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    InputEvents &events = Instance();
}

void InputEvents::PollEvents()
{
    glfwPollEvents();
}
