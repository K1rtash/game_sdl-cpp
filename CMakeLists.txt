cmake_minimum_required(VERSION 3.10)
project(game_sdl)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Archivos fuente
add_executable(${PROJECT_NAME} source/main.cpp)


# Rutas de SDL3
set(SDL3_INCLUDE "C:/DEV/SDL3/x64/include")
set(SDL3_LIB "C:/DEV/SDL3/x64/lib")

# Incluir headers (equivale a -I)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE})

# Incluir directorio de librerías (equivale a -L)
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIB})

# Enlazar librerías (equivale a -lSDL3)
target_link_libraries(${PROJECT_NAME} SDL3)



add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copiando SDL3.dll..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/caton/Desktop/Programacion/C++/Proyectos/game_sdl/lib/SDL3/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)



# --- SDL3_image ---
set(SDL3_IMAGE_INCLUDE "C:/DEV/SDL3_image/x64/include")
set(SDL3_IMAGE_LIB "C:/DEV/SDL3_image/x64/lib")
set(SDL3_IMAGE_BIN "C:/DEV/SDL3_image/x64/bin/SDL3_image.dll")

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_INCLUDE})
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_LIB})
target_link_libraries(${PROJECT_NAME} SDL3_image)

# Copiar SDL3_image.dll al directorio del .exe después de compilar
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL3_IMAGE_BIN}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copiar ASSETS al directorio .exe después de compilar

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
