#include <window/hud/widget.h>

#include <vector>
#include <string>
#include <memory>
namespace rpg::hud {
/*! \brief A group of widgets that can be enabled or disabled */
class Group : public Widget {
 private:
  std::vector<std::unique_ptr<Widget>> widgets;
  bool* enable_toggle = NULL;
  bool use_group;  //< If true, use an imgui collapsable group. Otherwise just
                   // have the elements appear without anything;

 public:
  std::string name;

  /*! \brief Create a new group with widgets
    \param widgets Widgets to contain within this group.
    \param name Name of the group. This will be drawn if use_group is true
    \param use_group Whether or not to use an ImGUI group or just draw all
    widgets as if they were within the window
  */
  Group(const std::string& name,
        const std::vector<Widget*> widgets,
        bool use_group = true);

  /*! \brief Draw the group and all it's elements. */
  void Draw();

  /*! \brief Delete this group and all it's contents */
  ~Group(){};
};
}  // namespace rpg::hud