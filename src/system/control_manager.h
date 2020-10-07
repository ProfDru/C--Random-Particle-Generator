#pragma once
#include <system/control_enums.h>
#include <system/bindings.h>

#include <vector>
namespace rpg::input {

class InputManager {
 private:
  /*! \brief Get the state of this action */
  static KEY_STATE GetKeyState(ACTION action);

  inline static double cursor_x = 0;
  inline static double cursor_y = 0;

  /*! \brief Update the state of an action */
  static void SetState(ACTION action, KEY_STATE state);

  static std::vector<KEY_STATE>
      action_states;  //< A vector containing the state of every possible action

 public:
  static Bindings current_bindings;  //< Set of bindings currently in use.

  /*! \brief Set the action belonging to this key as pressed or unpressed */
  static void RecordChangeInKeyState(bool is_down, int key_code);

  /*! \brief Change the current set of bindings. */
  static void SetBindings(const Bindings& binds);

  /*! \brief Deteremine if an action is currently active.
      \returns `true` if the action is currently active
      \returns `false` if the action isn't active
 */
  static bool IsActive(ACTION action);

  /*! \brief Get the current Corsor XY Position */
  static double GetCursorX();
  static double GetCursorY();

  /*! \brief Update the X and Y position of the cursor */
  static void UpdateCursorXY(double x, double y);

  /*! \brief Get an array of the all actions that are currently active.*/
  static std::vector<ACTION> GetCurrentActions();
};
}  // namespace rpg::input