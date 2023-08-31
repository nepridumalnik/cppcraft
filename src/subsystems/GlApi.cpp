#include <GlApi.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdexcept>

GlApi::GlApi()
{
    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error{"Failed while glfwInig()"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

GlApi::~GlApi()
{
    glfwTerminate();
}

GlApi &GlApi::Instance()
{
    static GlApi api;
    return api;
}

GLFWwindow *GlApi::CreateWindow(uint32_t width, uint32_t height, const std::string_view title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if (!window)
    {
        throw std::runtime_error{"Window has not being created"};
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error{"Failed while glewInit()"};
    }

    glViewport(0, 0, width, height);
    glClearColor(0.6f, 0.62f, 0.65f, 1.0f);

    return window;
}
