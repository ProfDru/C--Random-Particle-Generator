#pragma once

#include <window/hud/widget.h>

#include <string>
#include <functional>

namespace rpg::hud {
class Label : public Widget {
 private:
  bool is_automatic;  //< If true update the label every frame by calling the
                      // update function
  std::function<std::string()> string_function;

 public:
  std::string name;
  std::string text;

  /*! \brief Create a label that displays a constant value */
  Label(const std::string& name, const std::string& text);

  /*! \brief Create a label that will display the output from `update_function`
   * every frame
   */
  Label(const std::string& name, std::function<std::string()> update_function);

  virtual void Draw() override;

  void UpdateText(std::string& new_text);

  ~Label(){};
};
}  // namespace rpg::hud