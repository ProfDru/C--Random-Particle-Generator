#include <window/hud/widget.h>

#include <string>
namespace rpg::hud {
class Label : public Widget {
 public:
  std::string text;

  Label(const std::string& name, const std::string& text);

  void Draw() override;

  void UpdateText(std::string& new_text);

  ~Label(){};
};
}  // namespace rpg::hud