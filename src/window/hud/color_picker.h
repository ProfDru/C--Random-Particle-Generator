#pragma once

#include <window/hud/widget.h>

namespace rpg::hud {

/*! \brief A RGB color picker  */
class ColorPicker : public Widget {
 public:
  float* color_ptr = NULL;

 public:
  std::string name;
  /*! \brief  Construct a new ColorPicker  */
  ColorPicker(const std::string& name, float* color_ptr);

  void Draw() override;
  ~ColorPicker(){};
};
}  // namespace rpg::hud