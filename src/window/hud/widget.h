#pragma once

#include <string>

namespace rpg::hud {

/*! \brief The base element of the Heads Up Display

    \details Widgets cannot be used ontheir own, and must be added
    to hud windows in order to function.

    \see hud::Window for more information about the process.
*/
class Widget {
 public:
  std::string name;  //< Name of this widget
  std::string help_marker =
      "";  //< Text that will appear when the help marker is hovered over
  bool same_line = false;  //< Whether or not this widget should be drawn on the
                           //same line as the last.
  /*! \brief Draw this hud element. */
  virtual void Draw() = 0;

  /*! \brief Set the help marker for this object.

    A help marker is a little question mark that appears next to an object which
    reveals more information when hovered over. If this is never set, then no
    help icon will appear once the widget is drawn. */
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