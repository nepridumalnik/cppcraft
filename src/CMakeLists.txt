find_package(glew REQUIRED)
find_package(glfw3 REQUIRED)

set(TARGET cppcraft)

set(SOURCES
    main.cpp
)

set(INCLUDES

)

set(LIBRARIES
    GLEW::GLEW
    glfw
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
