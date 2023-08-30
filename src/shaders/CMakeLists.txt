set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
set(GENERATED_FILE_CONTENT "#pragma once\n\n#include <string_view>\n")

file(GLOB VERTEX_SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.glslv)
file(GLOB FRAGMENT_SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.glslf)

set(SHADER_FILES
    ${VERTEX_SHADER_FILES}
    ${FRAGMENT_SHADER_FILES}
)

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)

    message("-- Generating shader: ${SHADER_NAME}")

    # Чтение содержимого файла
    file(READ ${SHADER_FILE} SHADER_CONTENT)
    
    # Замена двойных кавычек на '\"'
    string(REPLACE ";" "\;" SHADER_CONTENT "${SHADER_CONTENT}")
    string(REPLACE "\"" "\\\"" SHADER_CONTENT "${SHADER_CONTENT}")
    string(REPLACE "\n" "\\n" SHADER_CONTENT "${SHADER_CONTENT}")


    # Исключение пробелов из названий
    string(REPLACE " " "_" SHADER_NAME ${SHADER_NAME})
    
    # Добавление строки к сгенерированному файлу
    string(REPLACE ";" "\;" GENERATED_FILE_CONTENT ${GENERATED_FILE_CONTENT})
    set(GENERATED_FILE_CONTENT "${GENERATED_FILE_CONTENT}\nstatic constexpr std::string_view ${SHADER_NAME} = \"${SHADER_CONTENT}\"\;\n")
endforeach()

set(GENERATED_FILE ${GENERATED_DIR}/shaders.hpp)
file(WRITE ${GENERATED_FILE} ${GENERATED_FILE_CONTENT})
