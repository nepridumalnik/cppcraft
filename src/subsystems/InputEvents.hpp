#pragma once

class GLFWwindow;

class InputEvents
{
public:
    void PollEvents();
    void SetCurrentWindow(GLFWwindow *window);

    static InputEvents &Instance();

private:
    InputEvents() = default;
    ~InputEvents() = default;

    InputEvents(const InputEvents &) = delete;
    void operator=(const InputEvents &) = delete;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
};
