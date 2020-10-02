#include <concepts>

namespace rpg {

class Entity {
 private:
  int id;

 public:
  void SetID();

  /*! \brief Get the ID of this entity */
  int GetID() const;
}

}  // namespace rpg