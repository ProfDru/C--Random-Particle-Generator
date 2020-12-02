# CMakeList.txt : CMake project for RandomParticleEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("RandomParticleEngine")


# Set compiler commands
set(GENERAL_COMPILER_OPTIONS
)

set(RELEASE_OPTIONS
  -Ofast
  -flto
  -fuse-linker-plugin
  -pipe
  -fomit-frame-pointer
)

set(RELEASE_DEBUG_OPTIONS
  -Ofast
  -g
  -Wall
)

set(DEBUG_OPTIONS
  -Wall
  -Wextra
  -Og
  -g
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Compile Options
# set(CMAKE_CXX_CLANG_TIDY "C:\\msys64\\mingw64\\bin\\clang-tidy.exe" -p=${CMAKE_BINARY_DIR})

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
    src/utils.h
    src/utils.cpp

    src/sys_time.cpp
    src/camera.cpp
    src/scene.cpp
    src/main.cpp
    src/random_or_constant.h
    src/random_or_constant.cpp

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
    src/window/window.cpp
    src/window/window.h

    src/window/hud/hud_window.cpp
    src/window/hud/hud_window.h
    src/window/hud/widget.h
    src/window/hud/widget.cpp
    src/window/hud/label.h
    src/window/hud/label.cpp
    src/window/hud/button.h
    src/window/hud/button.cpp
    src/window/hud/slider.h
    src/window/hud/slider.cpp
    src/window/hud/combo.h
    src/window/hud/combo.cpp
    src/window/hud/fps_counter.h
    src/window/hud/fps_counter.cpp
    src/window/hud/group.cpp
    src/window/hud/group.h
    src/window/hud/checkbox.h
    src/window/hud/checkbox.cpp
    src/window/hud/optional_element.h
    src/window/hud/optional_element.cpp
    src/window/hud/color_picker.h
    src/window/hud/color_picker.cpp 
    src/window/hud/multi_widget.cpp
    src/window/hud/multi_widget.h

    src/menus/roc_control.cpp
    src/menus/roc_control.h
    src/menus/settings.cpp
    src/menus/settings.h

    src/math/vector3d.h
    src/math/units.h
    src/math/base.h
    src/math/color.h
    src/math/random/random_manager.h
    src/math/random/random_manager.cpp
    src/math/random/random_enums.h
    src/math/random/distribution.cpp
    src/math/random/distribution.h
    src/math/random/generator.cpp
    src/math/random/generator.h
    src/math/random/distributions/uniform.cpp
    src/math/random/distributions/uniform.h
    src/math/random/distributions/normal.cpp
    src/math/random/distributions/normal.h
    src/math/random/distributions/log_normal.h
    src/math/random/distributions/log_normal.cpp
    src/math/random/distributions/general.cpp
    src/math/random/distributions/general.h

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
    src/entities/particle_color_algs.cpp
    src/entities/particle_color_algs.h

    src/glfw_bindings.h
    src/glfw_bindings.cpp

)
target_include_directories(RandomParticleEngine PRIVATE src) 

# Link main with it's dependencies
target_link_libraries(RandomParticleEngine PRIVATE
    ${OPENGL_LIBRARY}
    glfw
    glew_s
    imgui_glfw_opengl3
)

set_property(
  TARGET RandomParticleEngine
  PROPERTY CXX_STANDARD 20
)



message([status] ${CMAKE_BUILD_TYPE})
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  list(APPEND GENERAL_COMPILER_OPTIONS ${RELEASE_OPTIONS})
  message("USING RELEASE OPTIMIZATIONS")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
  list(APPEND GENERAL_COMPILER_OPTIONS ${RELEASE_DEBUG_OPTIONS})
  message("USING DEBUG-RELEASE OPTIMIZATIONS")
else()
  list(APPEND GENERAL_COMPILER_OPTIONS ${DEBUG_OPTIONS})
  message("USING DEBUG")
endif()

target_compile_options(
  RandomParticleEngine PRIVATE ${GENERAL_COMPILER_OPTIONS}
)

add_custom_command(
        TARGET RandomParticleEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders
)