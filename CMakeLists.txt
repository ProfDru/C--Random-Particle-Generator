# CMakeList.txt : CMake project for RandomParticleEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("RandomParticleEngine")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Compile Options
set(CMAKE_CXX_CLANG_TIDY "C:\\msys64\\mingw64\\bin\\clang-tidy.exe" -p=${CMAKE_BINARY_DIR})
# Disable clang tidy for now. There's an issue using this with this toolchain since it can't find opengl
# headers
set(CXX_STANDARD 20)

include(FetchContent)

# Runs through the process of fetching content from a url and building it
# as a a dependency
function(build_depend_from_git depend_name url)
  FetchContent_Declare(
    ${depend_name}
    GIT_REPOSITORY ${url}
  )

  FetchContent_GetProperties(${depend_name})
  if(NOT ${depend_name}_POPULATED)
    FetchContent_Populate(${depend_name})
    add_subdirectory(${${depend_name}_SOURCE_DIR} ${${depend_name}_BINARY_DIR})
  endif()
endfunction()

# Setup dependencies
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
build_depend_from_git(glfw https://github.com/glfw/glfw)
add_subdirectory(external)

# Setup main
add_executable(RandomParticleEngine)
target_sources(RandomParticleEngine
    PRIVATE 
    src/scene.h
    src/shader.h
    src/particle_system.h
    src/controls.h
    src/utils.h
    src/particle_simulation.h
    src/particle.h
    src/random_manager.cpp
    src/sys_time.cpp

    src/camera.cpp
    src/particle_system.cpp
    src/scene.cpp
    src/main.cpp
    src/shader.cpp
    src/controls.cpp
    src/particle_simulation.cpp
    src/particle.cpp
    src/random_manager.h
    src/sys_time.h

    src/math/vector3d.h
    src/math/units.h
    src/math/base.h

    src/physics/base.h
    src/physics/kinematics.h
    src/physics/rigid_body.h
)
target_include_directories(RandomParticleEngine PRIVATE src) 

# Link main with it's dependencies
target_link_libraries(RandomParticleEngine PRIVATE
    ${OPENGL_LIBRARY}
    glfw
    glew_s
)

set_property(
  TARGET RandomParticleEngine
  PROPERTY CXX_STANDARD 20
)

target_compile_options(
  RandomParticleEngine PRIVATE -Wall -Wextra
)

add_custom_command(
        TARGET RandomParticleEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders
)