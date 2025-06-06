cmake_minimum_required(VERSION 3.28.3)

project(run)

# Include Conan-generated files for proper linking
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Find + include headers for opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find header for nlohmann/json
find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Exe file + linked
# Executable + source files
add_executable(${PROJECT_NAME}
    src/annotationCheck.h
    src/annotationCheck.cc
    src/main.cc
)

add_executable(split
    src/tools/splitVideoTool.cc
)

target_link_libraries(${PROJECT_NAME}  
    PRIVATE ${OpenCV_LIBS}
    PRIVATE ${nlohmann_json_LIBRARIES}
)

target_link_libraries(split 
    PRIVATE ${OpenCV_LIBS}
    PRIVATE ${nlohmann_json_LIBRARIES}
)

# Puts the exe file in the parent directory of the build directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)

set_target_properties(split PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)