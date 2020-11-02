#pragma once
#include <window\hud\widget.h>
#include <memory>

namespace rpg::hud {

/*! \brief A widget that can alternatively display one of two widgets */
class AlternateWidget : public Widget {
 private:
  std::unique_ptr<Widget> true_widget = NULL;
  std::unique_ptr<Widget> false_widget = NULL;
  std::string checkbox_title = "";
  bool use_builtin_checkbox = false;

 public:
  bool widget_state = true;
  bool* bool_to_track = NULL;

  /*! \brief Create a widget with it's own internal checkbox to toggle between
   * elements */
  AlternateWidget(Widget* true_widget,
                  Widget* false_widget,
                  std::string checkbox_title = "");

  /*! \brief Create a widget that montiors a boolean value and toggles based on
   * that */
  AlternateWidget(Widget* true_widget,
                  Widget* false_widget,
                  bool* bool_to_track);

  void Draw();

  ~AlternateWidget(){};
};

}  // namespace rpg::hud