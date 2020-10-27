#include <menus\settings.h>

#include <window/hud_manager.h>
#include <window/hud/hud_window.h>

#include <entities/particle_simulation.h>

#include <window/hud/label.h>
#include <window/hud/slider.h>
#include <window/hud/button.h>
#include <window/hud/fps_counter.h>

using namespace rpg::hud;
using std::string;
using std::vector;
namespace rpg::menus {

std::string GetParticleCount(const ParticleEngine* ps) {
  return "Particle Count: " + std::to_string(ps->NumVertices());
}

void InitParticleMenu(const rpg::ParticleEngine* PE) {
  vector<Widget*> options_widgets = {new Slider("Simulation Timescale",
                                                "Simulation Timescale",
                                                &rpg::simulation::time_scale)};

  vector<Widget*> fps_widgets{
      new FPSCounter("FrameCounter"),
      new Label("Particle Counter", std::bind(GetParticleCount, PE))};

  HudManager::CreateWindow("Options");

  for (const auto& widget : options_widgets)
    HudManager::AddWidget("Options", widget);

  HudManager::CreateWindow("Performance Metrics", 0, 640, true);
  for (const auto& widget : fps_widgets)
    HudManager::AddWidget("Performance Metrics", widget);
}
}  // namespace rpg::menus