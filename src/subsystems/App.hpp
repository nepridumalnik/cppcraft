#pragma once

class App
{
public:
    App() = default;

    void Run();

private:
    App(const App &) = delete;
    void operator=(const App &) = delete;

private:
    static constexpr int m_defaultWidth = 800;
    static constexpr int m_defaultHeight = 600;
};
