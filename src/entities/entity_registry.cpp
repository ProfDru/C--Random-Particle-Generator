#include <entities/entity_registry.h>

namespace rpg {
int Registry::next_id = 0;
int Registry::GetNextID() {
  int next = next_id;
  next_id++;
  return next;
}

}  // namespace rpg