#pragma once
#include <window\hud\widget.h>
#include <memory>
#include <vector>

namespace rpg::hud {

/*! \brief A widget that can alternatively display one of many widgets */
class MultiWidget : public Widget {
 private:
  std::vector<std::unique_ptr<Widget>> widgets;
  std::string checkbox_title = "";
  bool use_builtin_checkbox = false;

 public:
  const int* int_to_watch;

  /*! \brief Create a multi-widget from an ordered array of widgets */
  MultiWidget(const std::vector<Widget*>& widgets, const int* int_to_watch);

  void Draw() override;

  ~MultiWidget(){};
};

}  // namespace rpg::hud