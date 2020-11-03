#include <window\hud\optional_element.h>
#include <imgui.h>

namespace rpg::hud {
AlternateWidget::AlternateWidget(Widget* true_widget,
                                 Widget* false_widget,
                                 std::string checkbox_title)
    : true_widget(true_widget),
      false_widget(false_widget),
      checkbox_title(checkbox_title) {
  use_builtin_checkbox = !checkbox_title.empty();
}

AlternateWidget::AlternateWidget(Widget* true_widget,
                                 Widget* false_widget,
                                 bool* bool_to_track)
    : true_widget(true_widget),
      false_widget(false_widget),
      bool_to_track(bool_to_track) {}

void AlternateWidget::Draw() {
  if (bool_to_track != NULL)
    this->widget_state = *bool_to_track;

  if (widget_state && true_widget) {
    true_widget->Draw();
    true_widget->DrawHelpMarker();
  } else if (false_widget) {
    false_widget->Draw();
    false_widget->DrawHelpMarker();
  }

  if (use_builtin_checkbox) {
    ImGui::SameLine();
    ImGui::Checkbox(checkbox_title.c_str(), &this->widget_state);
  }
}
}  // namespace rpg::hud