#include <scene.h>

#include <rendering\renderer.h>
#include <rendering\preloaded_shaders.h>

#include <entities/entity.h>
#include <entities/entity_registry.h>
#include <entities/particle_simulation.h>

#include <system/control_manager.h>
#include <system\kbm_movement.h>

#include <utils.h>

#include <menus/settings.h>

#include <cassert>
#include <exception>
#include <iostream>
#include <string>

namespace rpg {

float camera_speed = 2.5f;
float camera_boost_multi = 2.5f;

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
  this->main_camera = Camera(0, 0, 2, 0, 0, -1);

  // Set the ID of the particle system
  this->PI.SetID(Registry::GetNextID());

  // Add hud widgets
  rpg::menus::InitParticleMenu(&PI, &main_camera, &camera_speed,
                               &camera_boost_multi);

  // Initiate draw loop
  printf("Beginning Draw Loop. \n");
  this->DrawLoop();
}

inline bool HandleMovement(Camera& camera, GLFWwindow* window) {
  auto movement = Move(camera_speed, camera_boost_multi);
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
  rendering::Renderer::AssignShader(PI, rendering::ParticleShader);

  bool keep_drawing = true;

  this->current_window.UpdateSize();

  while (keep_drawing) {
    PI.Update();
    HandleMovement(this->main_camera, this->current_window.win);
    current_window.TrackMouse(input::InputManager::IsPaused());
    this->current_window.Clear();
    rendering::Renderer::Render(PI);
    keep_drawing = this->current_window.Redraw();
  }
}

}  // namespace rpg