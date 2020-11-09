#include <window\hud\combo.h>

#include <imgui.h>
#include <iostream>

namespace rpg::hud {

/*! \brief Concatenate all the strings in the vector to a single string
 * seperated by null characters */
std::string BuildString(const std::vector<std::string>& elements) {
  std::string output = "";

  for (const auto& element : elements) {
    output.append(element);
    output.append("\0");
  }

  std::cout << output << std::endl;
  return output;
}

ComboBox::ComboBox(const std::string& name,
                   const std::vector<std::string>& elements,
                   int* var)
    : Label(name, name), int_to_update(var), elements(elements) {
  this->values = BuildString(elements);
  *int_to_update = 0;
}

ComboBox::ComboBox(const std::string& name,
                   const std::vector<std::string>& elements,
                   int* var,
                   std::function<void()> update_func)
    : Label(name, name),
      int_to_update(var),
      elements(elements),
      update_func(update_func) {
  this->values = BuildString(elements);
  *int_to_update = 0;
}

void ComboBox::check_update(int new_value) {
  if (new_value != last_value) {
    last_value = new_value;

    // dont call the function if it has no target
    if (update_func)
      update_func();
  }
}

void ComboBox::Draw() {
  // ImGui::Combo(this->text.c_str(), int_to_update, values.c_str());

  // This will be true if the drop down should be rendered
  if (ImGui::BeginCombo(this->name.c_str(),
                        this->elements[*int_to_update].c_str())) {
    // This is the drop down code specifically
    for (int i = 0; i < this->elements.size(); i++) {
      const bool is_selected = (i == *int_to_update);

      if (ImGui::Selectable(this->elements[i].c_str(), is_selected))
        *int_to_update = i;

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    this->check_update(*int_to_update);
    ImGui::EndCombo();
  }
}
}  // namespace rpg::hud