cmake_minimum_required(VERSION 3.16)
project(RogueliteGame VERSION 0.1.0 LANGUAGES C CXX)

# Definir o padr�o C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar diret�rios de sa�da
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Adicionar diret�rio de cabe�alhos
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.4/include
)

# Encontrar bibliotecas
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.4/lib/x64
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.4/lib/x86
)

# Coletar todos os arquivos fonte
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Criar execut�vel
add_executable(${PROJECT_NAME} ${SOURCES} "include/entities/Enemy.h" "src/entities/Enemy.cpp")

# Vincular bibliotecas
target_link_libraries(${PROJECT_NAME} 
    SDL3
    # Adicione aqui outras bibliotecas necess�rias, como SDL3_image, SDL3_ttf, etc.
)

# Copiar DLLs para o diret�rio de sa�da em sistemas Windows
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64-bit build
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.4/lib/x64" 
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    else()
        # 32-bit build
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.4/lib/x86" 
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif()

# Copiar recursos (assets)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)