#include <system/bindings.h>

#include <vector>
#include <cassert>

using std::vector;
namespace rpg::input {
inline void SetupBindings(vector<ACTION>& key_vector) {
  key_vector = vector<ACTION>(512, ACTION::NONE);
}

Bindings::Bindings() {
  SetupBindings(this->control_map);
}

Bindings::Bindings(const vector<Bind>& binds) {
  SetupBindings(this->control_map);

  for (const auto& bind : binds)
    this->AssignAction(bind.act, bind.keycode);
}

ACTION Bindings::GetAction(int key_code) const {
  // assert(keycode < control_map.size());
  return control_map[key_code];
}

void Bindings::AssignAction(ACTION act, int keycode) {
  if (keycode < this->control_map.size())
    this->control_map[keycode] = act;
}

}  // namespace rpg::input