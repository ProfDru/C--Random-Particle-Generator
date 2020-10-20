#pragma once

#include <string>

namespace rpg::hud {

class Widget {
 public:
  std::string name;
  std::string tooltip;
  std::string help_marker = "";

  virtual void Draw() = 0;

  /*! \brief Set the help marker for this object

    A help marker is a little question mark that appears next to an object which
    reveals more information when hovered over. This is useful when the
    information that is being presented doesn't have a clear spot for a tooltip.

  */
  virtual void SetHelpMarker(const std::string& help_text);

  /*! \brief Render the help marker for this object

      This will only render the help marker if it has been set to a non-empty
     string previously.


     \remarks This code is from the official ImGUI demo.

   */
  virtual void DrawHelpMarker();

  virtual ~Widget(){};
};
}  // namespace rpg::hud