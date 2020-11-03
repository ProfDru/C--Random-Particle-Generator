#pragma once
#include <window\hud\widget.h>
#include <memory>
#include <vector>

namespace rpg::hud {

/*! \brief A widget that can alternatively display one of many widgets */
class MultiWidget : public Widget {
 private:
  std::vector<std::unique_ptr<Widget>> widgets;
  std::vector<std::vector<int>> indicies_to_draw;
  std::string checkbox_title = "";
  const bool simple_mode = true;

  /*! \brief Draw the widget at the given index */
  void draw_widget(int index);

 public:
  const int* int_to_watch;

  /*! \brief Create a simploe multi-widget from an ordered array of widgets */
  MultiWidget(const std::vector<Widget*>& widgets, const int* int_to_watch);

  /*! \brief Create a multi-widget that reuses widgets in certain states

    \param widgets Widgets to use.
    \param indices Which values to draw which widgets for. For example if
    indicies[1] contained the integers 2 and 3, this would draw the elements are
    array indicies 2 and 3.
  */
  MultiWidget(const std::vector<Widget*>& widgets,
              const int* int_to_watch,
              const std::vector<std::vector<int>>& indices);

  void Draw() override;

  ~MultiWidget(){};
};

}  // namespace rpg::hud