cmake_minimum_required(VERSION 3.25)
project(cg_hw_cgame_of_life)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(${PROJECT_NAME}
        main.cpp
        ${SOURCES}
        ColorRGB.cpp ColorRGB.h Framebuffer.cpp Framebuffer.h Vertex2.h)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}/include
        PUBLIC ${PROJECT_SOURCE_DIR}/src
        )

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}

        )