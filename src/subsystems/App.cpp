#include <App.hpp>

#include <Window.hpp>
#include <InputEvents.hpp>
#include <Camera.hpp>

#include <graphics/Shader.hpp>
#include <graphics/Texture.hpp>

#include <generated/shaders.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <stdexcept>

void App::Run()
{
    static constexpr float vertices[] = {
        // x    y     z     u     v
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 1
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // 2
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // 3

        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 4
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // 5
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 6
    };

    InputEvents &events = InputEvents::Instance();

    Window window;
    window.Initialize(m_defaultWidth, m_defaultHeight, "CppCraft");

    auto shader = Shader::LoadShader(MainVert, MainFrag);
    auto texture = Texture::LoadTexture("D:/Programming/C++/minecraft/src/resources/images/texture_checker.png");

    uint32_t vao = 0;
    uint32_t vbo = 0;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera{{0.0f, 0.0f, 1.0f}, glm::radians(90.0f), m_defaultWidth / m_defaultHeight};

    const auto autoChangeAspect = [&camera](uint32_t w, uint32_t h) -> void
    {
        camera.SetAspect(w, h);
    };

    events.AddWindowResizeCallback(autoChangeAspect);

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(0.5f, 0, 0));

    float lastTime = glfwGetTime();
    float delta = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;

    static constexpr float speed = 5;

    while (!window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        const float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        events.PollEvents();

        if (events.KeyJPressed(GLFW_KEY_TAB))
        {
            window.ToggleCursor();
        }
        if (events.KeyPressed(GLFW_KEY_W))
        {
            camera.Pos(camera.Pos() + camera.Front() * delta * speed);
        }
        if (events.KeyPressed(GLFW_KEY_S))
        {
            camera.Pos(camera.Pos() - camera.Front() * delta * speed);
        }
        if (events.KeyPressed(GLFW_KEY_D))
        {
            camera.Pos(camera.Pos() + camera.Right() * delta * speed);
        }
        if (events.KeyPressed(GLFW_KEY_A))
        {
            camera.Pos(camera.Pos() - camera.Right() * delta * speed);
        }

        shader->Use();
        shader->UniformMatrix("model", model);

        glm::mat4 cameraProjview = camera.GetProjection() * camera.GetView();
        shader->UniformMatrix("projview", cameraProjview);
        texture->Bind();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        window.SwapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
