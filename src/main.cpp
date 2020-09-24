#include <iostream>
#include "scene.h"

int main() {
  std::cout << "Hello, World!" << std::endl;

  // Create the scene then pass control to it.
  rpg::Scene S;
  S.Start();

  return 0;
}