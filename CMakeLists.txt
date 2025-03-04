cmake_minimum_required(VERSION 3.10)
project(GreenTriangleProject LANGUAGES CXX C) # Modify this when changing the project name

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GLFW and GLM (system packages)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

set(HEADERS 
    libraries/framework.h
    libraries/glad/include/glad/glad.h
)
# Source files
set(SOURCES 
    GreenTriangleNaked.cpp # Modify this when changing files
    libraries/framework.cpp 
    libraries/glad/src/glad.c
)


# Create the executable
add_executable(GreenTriangle ${SOURCES} ${HEADERS})

# Include glad directory
target_include_directories(GreenTriangle PRIVATE . libraries libraries/glad/include)

# Link against GLFW and GLM
target_link_libraries(GreenTriangle PRIVATE glfw glm)
add_compile_definitions(_HAS_CXX17=1)


