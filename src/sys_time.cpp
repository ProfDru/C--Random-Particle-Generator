#include <chrono>

namespace rpg::system {
// All of this time stuff should be moved to its own class
using clock = std::chrono::high_resolution_clock;
using timems = std::chrono::time_point<clock>;
static timems last_time;

int get_time_ms() {
  timems current_time = clock::now();

  auto time_since_epoch = current_time.time_since_epoch();

  return std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch)
      .count();
}

}  // namespace rpg::system