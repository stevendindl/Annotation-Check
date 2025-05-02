cmake_minimum_required(VERSION 3.28.3)

project(run)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/main.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Puts the executable in the parent directory of the build directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../src
)