#include <window/hud/widget.h>

namespace rpg::hud {
class CheckBox : public Widget {
 private:
  bool* target = NULL;

 public:
  std::string name;

  /*! \brief Create a new checkbox that will update target upon being clicked.*/
  CheckBox(const std::string& name, bool* target);

  void Draw();

  ~CheckBox() {}
};
}  // namespace rpg::hud