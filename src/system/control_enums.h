#pragma once
namespace rpg::input {
enum class KEY_STATE { MINUS, PLUS, SIZE };

enum class ACTION {
  NONE,
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  BOOST,
  BRAKE,
  PAUSE,
  QUIT,
  USE,
  SIZE
};

}  // namespace rpg::input