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
  std::vector<std::string> elements;
  std::function<void()> update_func;
  int* int_to_update;
  int last_value;

  /*! \brief Compare the current value to the previous value and call
             the update function if it changed */
  void check_update(int new_value);

 public:
  /*! \brief Construct a new combo box with the given values

    When the value is changed it will update var to the index
    of the selected element.


  */
  ComboBox(const std::string& name,
           const std::vector<std::string>& elements,
           int* var);

 public:
  /*! \brief Construct a new combo box with the given values

    When the value is changed it will update var to the index
    of the selected element and call the given function

  */
  ComboBox(const std::string& name,
           const std::vector<std::string>& elements,
           int* var,
           std::function<void()> update_func);

  void Draw();
};
}  // namespace rpg::hud