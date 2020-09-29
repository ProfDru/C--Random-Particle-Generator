#include <random_manager.h>
#include <cmath>
namespace rpg::simulation {
float RandomManager::GetRandomNumber() {
  return RNG.GetRandomNumber(RD);
}

float RandomManager::random_range(float min, float max) {
  float random_number = GetRandomNumber();
  return std::lerp(min, max, random_number);
}

}  // namespace rpg::simulation