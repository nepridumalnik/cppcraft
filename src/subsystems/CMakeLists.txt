set(TARGET subsystems)

set(SOURCES
    App.cpp
    Window.cpp
    GlApi.cpp
    InputEvents.cpp
    Camera.cpp

    graphics/Shader.cpp
    graphics/Texture.cpp
)

set(LIBRARIES
    # Графика
    GLEW::GLEW
    glfw

    # Вспомогательные
    PNG::PNG
    glm::glm
)

set(INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})
