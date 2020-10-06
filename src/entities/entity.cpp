#include <entities/entity.h>

namespace rpg {

void Entity::SetID(int id) {
  this->id = id;
}

int Entity::GetID() const {
  return this->id;
}
}  // namespace rpg
