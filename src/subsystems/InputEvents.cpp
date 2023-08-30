#include <InputEvents.hpp>

#include <GLFW/glfw3.h>

InputEvents::InputEvents() : m_currentFrame{0}, m_xpos{0}, m_ypos{0}, m_coursorStarted{false} {}

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

    if (action == GLFW_PRESS)
    {
        events.m_pressedKeys[key] = {events.m_currentFrame, true};
    }
    else if (action == GLFW_RELEASE)
    {
        events.m_pressedKeys[key] = {events.m_currentFrame, false};
    }
}

void InputEvents::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    InputEvents &events = Instance();

    if (action == GLFW_PRESS)
    {
        events.m_clickedButtons[button] = {events.m_currentFrame, true};
    }
    else if (action == GLFW_RELEASE)
    {
        events.m_pressedKeys[button] = {events.m_currentFrame, false};
    }
}

void InputEvents::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    InputEvents &events = Instance();

    if (events.m_coursorStarted)
    {
        events.m_xpos += xpos - events.m_x;
        events.m_ypos += ypos - events.m_y;
    }
    else
    {
        events.m_coursorStarted = true;
    }

    events.m_x = xpos;
    events.m_y = ypos;
}

bool InputEvents::KeyPressed(int code)
{
    InputEvents &events = Instance();
    const auto it = events.m_pressedKeys.find(code);
    return it != events.m_pressedKeys.end();
}

bool InputEvents::KeyJPressed(int code)
{
    InputEvents &events = Instance();
    const auto it = events.m_pressedKeys.find(code);
    if (it != events.m_pressedKeys.end())
    {
        return it->second.pressed && it->second.frame == events.m_currentFrame;
    }

    return false;
}

void InputEvents::PollEvents()
{
    ++m_currentFrame;
    glfwPollEvents();
}
