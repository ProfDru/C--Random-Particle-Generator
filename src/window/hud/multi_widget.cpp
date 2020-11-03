#include <window\hud\multi_widget.h>
#include <imgui.h>

namespace rpg::hud {

MultiWidget::MultiWidget(const std::vector<Widget*>& widgets,
                         const int* int_to_watch)
    : widgets(widgets.begin(), widgets.end()), int_to_watch(int_to_watch) {}

MultiWidget::MultiWidget(const std::vector<Widget*>& widgets,
                         const int* int_to_watch,
                         const std::vector<std::vector<int>>& indices)
    : widgets(widgets.begin(), widgets.end()),
      int_to_watch(int_to_watch),
      indicies_to_draw(indices),
      simple_mode(false) {}

inline void MultiWidget::draw_widget(int index) {
  if (index < widgets.size() && index >= 0 && this->widgets[index])
    this->widgets[index]->Draw();
}
void MultiWidget::Draw() {
  const int index = *int_to_watch;
  if (simple_mode)
    this->draw_widget(index);

  else if (index <= indicies_to_draw.size() && index >= 0) {
    for (const int w_index : indicies_to_draw[index])
      this->draw_widget(w_index);
  }
}
}  // namespace rpg::hud
