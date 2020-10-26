#include <scene.h>
#include <rendering\renderer.h>
#include <rendering\preloaded_shaders.h>
#include <entities/entity.h>
#include <entities/entity_registry.h>
#include <entities/particle_simulation.h>

#include <window/hud_manager.h>
#include <window/hud/label.h>
#include <window/hud/button.h>
#include <window/hud/widget.h>
#include <window/hud/slider.h>
#include <window/hud/combo.h>
#include <window/hud/fps_counter.h>

#include <system/control_manager.h>
#include <system\kbm_movement.h>
#include <utils.h>

#include <cassert>
#include <exception>
#include <iostream>
#include <string>

namespace rpg {

void SetupHud() {
  hud::Slider* time_slider =
      new hud::Slider("Simulation Timescale", "Simulation Timescale",
                      &rpg::simulation::time_scale);
  hud::FPSCounter* fps = new hud::FPSCounter("FrameCounter");

  HudManager::CreateWindow("Options");
  HudManager::AddWidget("Options", time_slider);
  HudManager::AddWidget("Options", fps);
}

void ScreenResizeCallback(float x, float y) {
  rpg::rendering::Renderer::UpdateScreenXY(x, y);
}

void Scene::Start() {
  // Initialize the window and set all callbacks
  this->current_window.SetResizeCallback(ScreenResizeCallback);
  this->current_window.SetMouseCallback(
      rpg::input::InputManager::UpdateCursorXY);
  this->current_window.SetKeyCallback(
      rpg::input::InputManager::RecordChangeInKeyState);
  this->current_window.Init(1280, 720);
  this->current_window.SetWindowFocusCallback(
      rpg::input::InputManager::TrackMouse);

  // Create a particle engine and camera
  printf("Creating Particle Engine and Camera...");
  this->PI.emplace(ParticleEngine());
  this->main_camera = Camera(0, 0, 2, 0, 0, -1);

  // Set the ID of the particle system
  this->PI->SetID(Registry::GetNextID());

  // Add hud widgets
  SetupHud();

  // Initiate draw loop
  printf("Beginning Draw Loop. \n");
  this->DrawLoop();
}

inline bool HandleMovement(Camera& camera, GLFWwindow* window) {
  auto movement = Move();
  if (!movement.empty()) {
    camera.Move(movement.position_change, movement.direction_change);
    glm::mat4 MVP = camera.CalculateMVP();
    rendering::Renderer::UpdateMVP(MVP);
    return true;
  } else
    return false;
}

void Scene::DrawLoop() {
  // Ensure we can capture the escape key being pressed below
  rendering::Renderer::AssignShader(*(this->PI), rendering::ParticleShader);

  bool keep_drawing = true;

  this->current_window.UpdateSize();

  while (keep_drawing) {
    PI->Update();
    HandleMovement(this->main_camera, this->current_window.win);
    current_window.TrackMouse(input::InputManager::IsPaused());
    this->current_window.Clear();
    rendering::Renderer::Render(*(this->PI));
    keep_drawing = this->current_window.Redraw();
  }
}

}  // namespace rpg