cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Renderer)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(lib/glfw)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Assimp lib only")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp lib only")

add_subdirectory(lib/assimp)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

# Include GLAD directories
include_directories("lib")
include_directories("lib/glad/include")
include_directories("lib/glfw/include")
include_directories("lib/glm/include")
include_directories("lib/assimp/include")
include_directories("src/headers")


# Set source files
set(SRC
    src/main.cpp
    lib/glad/src/glad.c
)

# Add executable
add_executable(Renderer WIN32 ${SRC})

# Link libraries
target_link_libraries(Renderer ${OPENGL_LIBRARIES} glfw assimp)

if(MSVC)
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message("\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n")
    else()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GLFW-CMake-starter)
    endif()
endif()