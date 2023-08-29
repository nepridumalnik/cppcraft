find_package(glew REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET cppcraft)

set(SOURCES
    main.cpp

    subsystems/App.cpp
    subsystems/Window.cpp
    subsystems/GlApi.cpp
    subsystems/Events.cpp
)

set(LIBRARIES
    GLEW::GLEW
    glfw
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
