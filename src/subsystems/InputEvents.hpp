#pragma once

#include <unordered_map>
#include <functional>

class GLFWwindow;

class InputEvents
{
public:
    void PollEvents() noexcept;
    void SetCurrentWindow(GLFWwindow *window) noexcept;

    bool KeyPressed(int code) const noexcept;
    bool KeyJPressed(int code) const noexcept;

    static InputEvents &Instance();

    void AddWindowResizeCallback(std::function<void(uint32_t, uint32_t)> cb) noexcept;

private:
    InputEvents();
    ~InputEvents() = default;

    InputEvents(const InputEvents &) = delete;
    void operator=(const InputEvents &) = delete;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) noexcept;
    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) noexcept;
    static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) noexcept;
    static void windowResizeCallback(GLFWwindow *window, int w, int h) noexcept;

private:
    struct KeyState
    {
        uint32_t frame;
        bool pressed;
    };

private:
    std::unordered_map<uint32_t, KeyState> m_pressedKeys;
    std::unordered_map<uint32_t, KeyState> m_clickedButtons;
    uint32_t m_currentFrame;

    bool m_coursorStarted;
    double m_xpos;
    double m_ypos;
    double m_x;
    double m_y;

    std::function<void(uint32_t, uint32_t)> m_cb;
};
