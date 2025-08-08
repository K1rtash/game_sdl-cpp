cmake_minimum_required(VERSION 3.10)
project(game_sdl)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# --- ICONO PARA WINDOWS ---
if(WIN32)
    # Usar ruta absoluta al icono
    get_filename_component(ICON_ABSOLUTE_PATH "${CMAKE_SOURCE_DIR}/assets/icon.ico" ABSOLUTE)
    
    # Crear archivo .rc temporal
    set(RC_CONTENT "IDI_ICON1 ICON \"${ICON_ABSOLUTE_PATH}\"")
    set(TEMP_RC_FILE "${CMAKE_CURRENT_BINARY_DIR}/temp_resources.rc")
    file(WRITE ${TEMP_RC_FILE} ${RC_CONTENT})
    
    # Compilar el recurso
    set(RESOURCE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources.res")
    add_custom_command(
        OUTPUT ${RESOURCE_OUTPUT}
        COMMAND windres -i ${TEMP_RC_FILE} -o ${RESOURCE_OUTPUT}
        DEPENDS ${ICON_ABSOLUTE_PATH}
        COMMENT "Compilando recursos para el icono"
    )
    
    add_executable(${PROJECT_NAME} source/main.cpp ${RESOURCE_OUTPUT})
endif()



# CONFIGURACION ANTIGUA

# Archivos fuente
#add_executable(${PROJECT_NAME} source/main.cpp)


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