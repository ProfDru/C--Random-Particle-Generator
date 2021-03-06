#include <menus\settings.h>

#include <window/hud_manager.h>
#include <window/hud/hud_window.h>

#include <entities/particle_simulation.h>
#include <entities/particle_system.h>

#include <glm/gtc/type_ptr.hpp>

#include <menus\roc_control.h>
#include <window/hud/label.h>
#include <window/hud/slider.h>
#include <window/hud/button.h>
#include <window/hud/fps_counter.h>
#include <window/hud/group.h>
#include <window/hud/checkbox.h>
#include <window/hud/optional_element.h>
#include <window/hud/color_picker.h>
#include <window/hud/combo.h>
#include <window/hud/multi_widget.h>

using namespace rpg::hud;
using std::string;
using std::vector;
namespace rpg::menus {

std::string GetParticleCount(ParticleEngine* ps) {
  return "Particle Count: " + std::to_string(ps->NumVertices() / 3);
}

/*! \brief Create a prebaked group to bind all parameters in a random or
 * constant */
Widget* BindRandomOrConstant(RandomOrConstant& ROC, const std::string& name) {
  return CreateDistributionWidgets(ROC, name);
}

std::string print_pos(const Camera* cam) {
  const auto pos = cam->get_pos();
  const auto rot = cam->get_rotation();

  return "x=" + std::to_string(pos[0]) + ",y=" + std::to_string(pos[1]) +
         ",z=" + std::to_string(pos[2]) + "\nhr=" + std::to_string(rot[0]) +
         ",vr=" + std::to_string(rot[1]);
}

void InitParticleMenu(rpg::ParticleEngine* PE,
                      Camera* camera,
                      float* camera_speed,
                      float* camera_speed_multiplier) {
  ColorPicker* start_color_picker =
      new ColorPicker("Gradient Begin Color", glm::value_ptr(PE->start_color));
  ColorPicker* end_color_picker =
      new ColorPicker("Gradient End Color", glm::value_ptr(PE->end_color));
  ComboBox* parameter_box = new ComboBox(
      "Scale Parameter",
      vector<string>{"Lifetime", "Distance from the ground", "Velocity"},
      reinterpret_cast<int*>(&PE->color_param));

  MultiWidget* color_pickers = new MultiWidget(
      {start_color_picker, end_color_picker, parameter_box},
      reinterpret_cast<const int*>(&PE->color_mode), {{0}, {2, 0, 1}, {2}});

  vector<Widget*> colors = {
      new ComboBox("ColorMode",
                   vector<string>{"Constant Color", "Gradient", "Rainbow"},
                   reinterpret_cast<int*>(&PE->color_mode)),
      color_pickers};

  vector<Widget*> simulation = {
      new Slider("Simulation Speed", &rpg::simulation::time_scale, 0.001f,
                 2.0f),
      new CheckBox("Enable Floor", &PE->bounce)};

  vector<Widget*> camera_settings = {
      new Label("Camera tracker", std::bind(print_pos, camera)),
      new Slider("Field of View", &(camera->fov), 20.0f, 120.0f),
      new Slider("Base Speed", camera_speed, 0.5f, 10.0f),
      new Slider("Boost/Brake Multiplier", camera_speed_multiplier, 1.25f,
                 3.0f),
  };

  vector<Widget*> particle_system{
      new Slider(
          "Number of Particles", &PE->max_particles, 1, 1000000,
          "Maximum number of particles that can be alive at any time. Once "
          "this cap is reached, no more particles will be created."),
      new Slider("Particle Lifetime", &PE->particle_lifetime, 0.1, 10,
                 "The time in seconds before a particle is destroyed."),

      new Slider("Horizontal Angle", &PE->horizontal_angle, 0, 360),
      BindRandomOrConstant(PE->vertical_angle, "Vertical Angle"),
      BindRandomOrConstant(PE->magnitude, "Magnitude"),
      new Slider("Particles Per Second", &PE->particles_per_second, 1, 200000,
                 "Number of particles that can be created per second.")};

  vector<Widget*> physics = {new AlternateWidget(
      new Slider("CoR", &PE->coeff_of_restitution, 0, 1,
                 "Coefficent of Restitution. Determines how much energy is "
                 "lost by a particle upon bouncing."),
      new Label("Enable boucning to edit CoR.", "Enable bouncing to edit CoR."),
      &PE->bounce)};

  std::vector<Widget*> options_widgets = {
      new Group("Camera", camera_settings, true),
      new Group("Simulation", simulation, true),
      new Group("Colors", colors, true),
      new Group("Particle System", particle_system, true),
      new Group("Particle Physics", physics, true)};

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