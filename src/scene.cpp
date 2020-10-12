#include <scene.h>
#include <rendering\renderer.h>
#include <rendering\preloaded_shaders.h>
#include <entities/entity.h>
#include <entities/entity_registry.h>

#include <system/control_manager.h>
#include <system\kbm_movement.h>
#include <utils.h>

#include <cassert>
#include <exception>
#include <iostream>

namespace rpg {

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
      rpg::input::InputManager::SetWindowFocus);

  // Create a particle engine and camera
  printf("Creating Particle Engine and Camera...");
  this->PI.emplace(ParticleEngine());
  this->main_camera = Camera(0, 0, 2, 0, 0, -1);

  // Set the ID of the particle system
  this->PI->SetID(Registry::GetNextID());

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
    this->current_window.Clear();
    rendering::Renderer::Render(*(this->PI));
    keep_drawing = this->current_window.Redraw();
  }
}

}  // namespace rpg