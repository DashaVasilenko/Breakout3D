cmake_minimum_required(VERSION 3.1)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(PATH_TO_VCPKG "" CACHE PATH "") 
include(${PATH_TO_VCPKG}/scripts/buildsystems/vcpkg.cmake)

find_package (OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package (GLEW REQUIRED STATIC)

file(GLOB SOURCES
    "src/*.cpp"
    "src/window/*.cpp"
    "src/renderer/*.cpp"
    "src/math/*.cpp"
    "src/core/*.cpp"
    "src/scene/*.cpp"
    "src/physics/*.cpp"
    "src/game/*.cpp"
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
add_executable(game ${SOURCES})
target_include_directories(game PUBLIC src)
target_link_libraries(game PRIVATE ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} glfw) 