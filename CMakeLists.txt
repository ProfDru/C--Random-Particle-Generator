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
#set(NANOGUI_BUILD_GLFW false)
#set(NANOGUI_BUILD_PYTHON false)
#set(NANOGUI_BUILD_SHARED false)
#set(NANOGUI_BACKEND OpenGL)
#set(NANOGUI_BUILD_EXAMPLES False)

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
build_depend_from_git(glfw https://github.com/glfw/glfw)
add_subdirectory(external)
#build_depend_from_git(nanogui https://github.com/mitsuba-renderer/nanogui)


# Setup main
add_executable(RandomParticleEngine)
target_sources(RandomParticleEngine
    PRIVATE 

    src/scene.h
    src/utils.h

    src/random_manager.cpp
    src/sys_time.cpp
    src/camera.cpp
    src/scene.cpp
    src/main.cpp

    src/random_manager.h
    src/sys_time.h

    src/system/kbm_movement.cpp
    src/system/kbm_movement.h
    src/system/control_enums.h
    src/system/bindings.cpp
    src/system/bindings.h
    src/system/control_manager.h
    src/system/control_manager.cpp
    
    src/rendering/shader.h
    src/rendering/shader.cpp
    src/rendering/shader_manager.h
    src/rendering/shader_manager.cpp
    src/rendering/renderer.h
    src/rendering/renderer.cpp
    src/rendering/preloaded_shaders.h
    src/rendering/shader_loader.cpp
    src/rendering/shader_loader.h
    src/rendering/draw.h
    src/rendering/draw.cpp

    src/window/hud_manager.cpp
    src/window/hud_manager.h
    src/window/hud_window.cpp
    src/window/hud_window.h
    src/window/window.cpp
    src/window/window.h

    src/math/vector3d.h
    src/math/units.h
    src/math/base.h

    src/physics/base.h
    src/physics/kinematics.h
    src/physics/rigid_body.h

    src/entities/entity.h
    src/entities/entity.cpp
    src/entities/entity_registry.cpp
    src/entities/entity_registry.h  
    src/entities/particle_simulation.cpp
    src/entities/particle.cpp
    src/entities/particle_simulation.h
    src/entities/particle.h
	  src/entities/particle_system.cpp
    src/entities/particle_system.h

    src/glfw_bindings.h
    src/glfw_bindings.cpp

)
target_include_directories(RandomParticleEngine PRIVATE src) 

# Link main with it's dependencies
target_link_libraries(RandomParticleEngine PRIVATE
    ${OPENGL_LIBRARY}
    glfw
    glew_s
#    nanogui
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