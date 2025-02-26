cmake_minimum_required(VERSION 3.10)
project(RogueliteGame VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SDL2 paths manually (adjust these paths to your SDL2 installation)
set(SDL2_DIR "C:/path/to/your/SDL2")
set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Copy SDL2.dll to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL2_DIR}/lib/x64/SDL2.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)