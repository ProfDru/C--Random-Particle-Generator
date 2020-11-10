#include <menus/roc_control.h>

#include <window/hud/checkbox.h>
#include <window/hud/slider.h>
#include <window/hud/optional_element.h>
#include <window/hud/group.h>

#include <functional>

namespace rpg {
using namespace rpg::hud;
using std::string;
using std::vector;

/*! \brief Used as a callback to create the required stuff for a random
 * distribution */
void ChangeRandomEngine(RandomOrConstant* roc) {
  printf(" CHANGE ENGINE \n");
}

/*! \brief Used as a callback to change the distribution a ROC is using */
void ChangeRandomDistribution(RandomOrConstant* roc) {
  printf("CHANGE DISTRIBUTION min:%f, max: %f\n", roc->rand_min, roc->rand_max);
}

Widget* CreateDistributionWidgets(RandomOrConstant& ROC,
                                  const std::string& name) {
  int* distribution_ptr = reinterpret_cast<int*>(&ROC.next_distribution);
  int* engine_ptr = reinterpret_cast<int*>(&ROC.next_algorithm);

  const vector<string> distributions{"Uniform", "Normal"};

  const vector<string> engines = {"Default", "MinSTD", "MT19937",
                                  "Ranlux48"
                                  "Ranlux48_B",
                                  "Knuth"};

  Widget* random_toggle = new CheckBox("Use random?", &ROC.use_random);
  Widget* engine_select = new ComboBox("Random Engine", engines, engine_ptr,
                                       std::bind(ChangeRandomEngine, &ROC));

  Widget* distribution_select =
      new ComboBox("Distribution", distributions, distribution_ptr,
                   std::bind(ChangeRandomDistribution, &ROC));

  Widget* min_slider =
      new Slider("min", &ROC.rand_min, ROC.min_value, ROC.max_value);
  Widget* max_slider =
      new Slider("max", &ROC.rand_max, ROC.min_value, ROC.max_value);
  Widget* constant_slider =
      new Slider(name, &ROC.constant, ROC.min_value, ROC.max_value);

  Widget* random_group =
      new Group("Random",
                vector<Widget*>{engine_select, distribution_select, max_slider,
                                min_slider},
                false);
  Widget* constant_group =
      new Group("Constant", vector<Widget*>{constant_slider}, false);

  Widget* random_constant_switcher =
      new AlternateWidget(random_group, constant_group, &ROC.use_random);

  Widget* final_group = new Group(
      name, vector<Widget*>{random_toggle, random_constant_switcher}, true);

  return final_group;
}

}  // namespace rpg