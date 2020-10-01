#include <random_manager.h>
#include <cmath>
#include <algorithm>
namespace rpg::simulation {
float RandomManager::GetRandomNumber() {
  return RNG.GetRandomNumber(RD);
}

float RandomManager::random_range(float min, float max) {
  float random_number = GetRandomNumber();
  random_number = static_cast<float>(math::wrap(random_number));
  return std::lerp(min, max, random_number);
}

}  // namespace rpg::simulation