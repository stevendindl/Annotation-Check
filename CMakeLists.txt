cmake_minimum_required(VERSION 3.28.3)

project(run)

# Find + include headers
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# FFigure out json library
# find_package(nlohmann_json REQUIRED)



# Exe file + linked
add_executable(${PROJECT_NAME} src/annotationCheck.h src/main.cc src/main2.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Puts the exe file in the parent directory of the build directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)