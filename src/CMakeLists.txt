include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})

add_subdirectory(shaders)
add_subdirectory(subsystems)

set(TARGET cppcraft)

set(SOURCES
    main.cpp
)

set(LIBRARIES
    subsystems
)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})
