#include <menus\settings.h>

#include <window/hud_manager.h>
#include <window/hud/hud_window.h>

#include <entities/particle_simulation.h>
#include <entities/particle_system.h>

#include <window/hud/label.h>
#include <window/hud/slider.h>
#include <window/hud/button.h>
#include <window/hud/fps_counter.h>

using namespace rpg::hud;
using std::string;
using std::vector;
namespace rpg::menus {

std::string GetParticleCount(ParticleEngine* ps) {
  return "Particle Count: " + std::to_string(ps->NumVertices());
}

void InitParticleMenu(rpg::ParticleEngine* PE) {
  vector<Widget*> options_widgets = {
      new Label("Simulation", "Simulation"),
      new Slider("Simulation Timescale", &rpg::simulation::time_scale),

      new Label("Particle System", "Particle System"),
      new Slider("Number of Particles", &PE->max_patricles, 1, 100000),
      new Slider("Particle Lifetime", &PE->particle_lifetime, 0.1, 60),
      new Slider("Horizontal Angle", &PE->angle, 0, 90)};

  vector<Widget*> fps_widgets{
      new FPSCounter("FrameCounter"),
      new Label("Particle Counter", std::bind(GetParticleCount, PE))};

  HudManager::CreateWindow("Options");

  for (const auto& widget : options_widgets)
    HudManager::AddWidget("Options", widget);

  HudManager::CreateWindow("Performance Metrics", 0, 640, true);
  for (const auto& widget : fps_widgets)
    HudManager::AddWidget("Performance Metrics", widget);
}  // namespace rpg::menus
}  // namespace rpg::menus