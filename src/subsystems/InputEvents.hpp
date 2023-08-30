#pragma once

#include <unordered_map>

class GLFWwindow;

class InputEvents
{
public:
    void PollEvents();
    void SetCurrentWindow(GLFWwindow *window);

    bool KeyPressed(int code);
    bool KeyJPressed(int code);

    static InputEvents &Instance();

private:
    InputEvents();
    ~InputEvents() = default;

    InputEvents(const InputEvents &) = delete;
    void operator=(const InputEvents &) = delete;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

private:
    struct KeyState
    {
        size_t frame;
        bool pressed;
    };

private:
    std::unordered_map<size_t, KeyState> m_pressedKeys;
    std::unordered_map<size_t, KeyState> m_clickedButtons;
    size_t m_currentFrame;

    bool m_coursorStarted;
    double m_xpos;
    double m_ypos;
    double m_x;
    double m_y;
};
