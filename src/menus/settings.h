#pragma once

#include <entities/particle_system.h>
#include <camera.h>
namespace rpg::menus {

/*! \brief Create and add the particle menu to the hudmanager*/
void InitParticleMenu(rpg::ParticleEngine* PE, Camera* camera);

}  // namespace rpg::menus