#pragma once

#include <vector>
#include <string>
#include <memory>

#include <window/hud/widget.h>

namespace rpg::hud {

/*! \brief A floating window that draws and manages the lifetime of a set of
  widgets

  \remarks
    The hud window is the fundamental part of the GUI, with each window
    able to be resized and moved around. The window handles the tasks
    of drawing and managing the widgets it contains. A window can be set
    as a HUD window to prevent it from being hidden while the simulation
    is unpaused.

*/
class Window {
  std::string name;
  float x, y;   //< Initial X,y position of the window
  bool is_hud;  //< Determines whether or not this window should draw while
                // paused

 private:
  std::vector<std::unique_ptr<Widget>> widgets;

 public:
  Window(const std::string& name,
         bool is_hud = false,
         float x_pos = 0,
         float y_pos = 0);

  /*! \brief Draw this window and all the widgets it contains. IF paused is true
   * and this is not a HUD window, this window will be hidden */
  void Draw(bool paused = false);

  /*! \brief Add a widget to this window.

  \note
    The order that widgets are drawn depends on the order in which they are
  added.

  \warning
    Once a widget is added, it's lifetime will be managed by this window. Do not
    attempt to delete a widget after it is added.
    */
  void AddWidget(Widget* widget);
};
}  // namespace rpg::hud