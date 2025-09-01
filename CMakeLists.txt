cmake_minimum_required(VERSION 3.10)
project(game_sdl)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.cpp")

# --- FLAGS ESTÁTICAS PARA MINGW (EVITAR DLLs) ---
if(MINGW)
    # Flags para linking estático de librerías de runtime de GCC
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(ICON_RC_FILE "${CMAKE_SOURCE_DIR}/app_icon.rc")
set(ICON_FILE "${CMAKE_SOURCE_DIR}/assets/icon.ico")


# --- ICONO DE LA APLICACION ---
if(WIN32 AND EXISTS ${ICON_FILE} AND EXISTS ${ICON_RC_FILE})
    message(STATUS "Configurando icono de la aplicación")
    add_executable(${PROJECT_NAME} ${SOURCES} ${ICON_RC_FILE})
    set_source_files_properties(${ICON_RC_FILE} PROPERTIES LANGUAGE RC)
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
    if(WIN32)
        message(WARNING "No se encontraron archivos de icono")
    endif()
endif()


# --- LIBRERIAS Y HEADERS ---

# SDL3 ---
set(SDL3_INCLUDE "C:/DEV/SDL3/x64/include")
set(SDL3_LIB "C:/DEV/SDL3/x64/lib")

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE}) # Equivale a -I
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIB}) # Equivale a -L
target_link_libraries(${PROJECT_NAME} SDL3)

# SDL3_image ---
set(SDL3_IMAGE_INCLUDE "C:/DEV/SDL3_image/x64/include")
set(SDL3_IMAGE_LIB "C:/DEV/SDL3_image/x64/lib")

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_INCLUDE}) # Equivale a -I
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_IMAGE_LIB}) # Equivale a -L 
target_link_libraries(${PROJECT_NAME} SDL3_image)

# GLM
target_include_directories(${PROJECT_NAME} PRIVATE "third-party/")


# --- EJECUTAR SCRIPT DE EMPAQUETADO ---
set(PACKAGE_SCRIPT "${CMAKE_SOURCE_DIR}/game/package.ps1")
set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND powershell -ExecutionPolicy Bypass -File "${PACKAGE_SCRIPT}"
    COMMENT "Empaquetando para distribución..."
)


# --- RUTAS ARCHIVOS POST-BUILD ---
#set(SDL3_IMAGE_BIN "C:/DEV/SDL3_image/x64/bin/SDL3_image.dll")
#set(SDL3_BIN "C:/DEV/SDL3/x64/bin/SDL3.dll")


# --- COPIAR AL DIRECTORIO BUILD TRAS HACER LA BUILD ---

# SDL3_image.dll
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL3_IMAGE_BIN}
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#)

# SDL3.dll
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL3_BIN}
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#)

# assets/
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${CMAKE_SOURCE_DIR}/assets"
#        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
#)

# options.txt
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${PROJECT_SOURCE_DIR}/game/options.txt"
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#)