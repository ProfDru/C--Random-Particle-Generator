#include <system/control_manager.h>
#include <glfw_bindings.h>
#include <scene.h>

#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;

  // Create the scene then pass control to it.
  rpg::Scene S;
  rpg::input::InputManager::SetBindings(rpg::input::GLFW_binds::binds);

  S.Start();

  return 0;
}