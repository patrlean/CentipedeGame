cmake_minimum_required(VERSION 3.26.5)
project(CentipedeGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/build")
set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/SFML/build/lib/Debug")

# include head files
include_directories(include)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

# source files
set(SOURCES
    src/Main.cpp
    src/Constants.cpp
    src/Spider.cpp
    src/Mushroom.cpp
    src/ECE_Centipede.cpp
    src/ECE_LaserBlast.cpp
    src/Mushroom.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_LIBRARY_DIR}/sfml-system-d-2.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/sfml-system-d-2.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_LIBRARY_DIR}/sfml-window-d-2.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/sfml-window-d-2.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_LIBRARY_DIR}/sfml-graphics-d-2.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/sfml-graphics-d-2.dll"
    COMMENT "Copying SFML DLLs to output directory")
endif()