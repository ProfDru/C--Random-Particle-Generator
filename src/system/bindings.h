#include <system/control_enums.h>
#include <vector>

namespace rpg::input {

/*! \brief An ordered way of storing actions */
struct Bind {
  int keycode;
  ACTION act;
};

class Bindings {
 public:
  /*! \brief Create an empty set of bindings */
  Bindings();

  /*! \brief Get the action for this keycode */
  ACTION GetAction(int keycode) const;

  void AssignAction(ACTION act, int keycode);
};

}  // namespace rpg::input