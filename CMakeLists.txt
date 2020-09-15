# CMakeList.txt : CMake project for RandomParticleEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("RandomParticleEngine")


# Setup dependencies
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# Setup main
add_executable(RandomParticleEngine)
target_sources(RandomParticleEngine
    PRIVATE 
    src/camera.cpp
    src/particle_system.cpp
    src/scene.cpp
    src/main.cpp
)
target_include_directories(RandomParticleEngine PRIVATE src) 

# Link sources
target_link_libraries(RandomParticleEngine PRIVATE
    ${OPENGL_LIBRARY}
    glfw
)

# TODO: Add tests and install targets if needed.
