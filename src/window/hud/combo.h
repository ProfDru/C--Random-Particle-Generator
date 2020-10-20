#pragma once

#include <window\hud\widget.h>
#include <window\hud\label.h>

#include <vector>
#include <string>
#include <functional>

namespace rpg::hud {
class ComboBox : public Label {
 private:
  // std::vector<std::string> values;
  std::string values;
  int* int_to_update;
  std::vector<std::string> elements;

 public:
  /*! \brief Construct a new combo box with the given values

    When the value is changed it will update var to the index
    of the selected element.


  */
  ComboBox(const std::string& name,
           const std::vector<std::string>& elements,
           int* var);

  void Draw();
};
}  // namespace rpg::hud