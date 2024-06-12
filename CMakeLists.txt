cmake_minimum_required(VERSION 3.27)


project(examp2)

set(CMAKE_BINARY_DIR bin)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)



include_directories(include)
add_executable(main src/main.cpp src/shader.cpp src/Matrices.cpp src/controls.cpp src/loader.cpp)


target_link_libraries(
    main
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw3
    glm::glm
    assimp
)
