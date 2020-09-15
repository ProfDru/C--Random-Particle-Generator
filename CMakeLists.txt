# CMakeList.txt : CMake project for RandomParticleEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("RandomParticleEngine")

# Add source to this project's executable.
add_executable(RandomParticleEngine)

target_sources(RandomParticleEngine PRIVATE 
               src/camera.cpp
               src/particle_system.cpp
               src/scene.cpp
               src/main.cpp
               )

target_include_directories(RandomParticleEngine PRIVATE src) 


# TODO: Add tests and install targets if needed.
