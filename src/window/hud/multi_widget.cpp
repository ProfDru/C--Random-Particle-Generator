#include <window\hud\multi_widget.h>
#include <imgui.h>

namespace rpg::hud {

MultiWidget::MultiWidget(const std::vector<Widget*>& widgets,
                         const int* int_to_watch)
    : widgets(widgets.begin(), widgets.end()), int_to_watch(int_to_watch) {}

void MultiWidget::Draw() {
  const int index = *int_to_watch;

  if (index < widgets.size() && index >= 0 && this->widgets[index])
    this->widgets[index]->Draw();
}

}  // namespace rpg::hud