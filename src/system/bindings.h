#pragma once
#include <system/control_enums.h>

#include <vector>
#include <functional>

namespace rpg::input {

/*! \brief An ordered way of storing actions */
struct Bind {
  int keycode;
  ACTION act;
};

class Bindings {
 private:
  std::vector<ACTION> control_map;

 public:
  /*! \brief Create an empty set of bindings */
  Bindings();

  /*! \brief Create a new binding set from an array of binds */
  Bindings(const std::vector<Bind>& binds);

  /*! \brief Get the action for this keycode */
  ACTION GetAction(int keycode) const;

  void AssignAction(ACTION act, int keycode);
};

}  // namespace rpg::input