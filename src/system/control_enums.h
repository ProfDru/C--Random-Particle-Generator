#pragma once
namespace rpg::input {
enum class KEY_STATE { MINUS = 0, PLUS = 1 };

enum class ACTION {
  NONE = 0,
  FORWARD = 1,
  BACKWARD = 2,
  LEFT = 3,
  RIGHT = 4,
  UP = 5,
  DOWN = 6,
  BOOST = 7,
  BRAKE = 8,
  PAUSE = 9,
  QUIT = 10,
  USE = 11,
  RESET = 12
};

}  // namespace rpg::input