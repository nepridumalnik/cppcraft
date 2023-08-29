#include <subsystems/App.hpp>

#include <iostream>

int main(int argc, char const *argv[])
{
    try
    {
        App app;
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
