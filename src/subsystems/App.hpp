#pragma once

#include <macro.hpp>

class App
{
public:
    EXPORT_SYMBOLS App() = default;
    EXPORT_SYMBOLS void Run();

private:
    App(const App &) = delete;
    void operator=(const App &) = delete;

private:
    static constexpr int m_defaultWidth = 800;
    static constexpr int m_defaultHeight = 600;
};
