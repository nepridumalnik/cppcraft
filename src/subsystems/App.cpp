#include <App.hpp>

#include <Window.hpp>

#include <graphics/Shader.hpp>
#include <graphics/Texture.hpp>

#include <generated/shaders.hpp>

#include <GL/glew.h>

#include <stdexcept>

void App::Run()
{
    static constexpr float vertices[] = {
        0, 0, 0, // a
        1, 0, 0, // b
        1, 1, 0, // c
    };

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    // glBindBuffer(0, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    while (!window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader->Use();
        texture->Bind();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.SwapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
