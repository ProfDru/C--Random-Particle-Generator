#include <menus/roc_control.h>

#include <math/random/distribution.h>
#include <math/random/distributions/normal.h>
#include <math/random/distributions/uniform.h>

#include <window/hud/checkbox.h>
#include <window/hud/slider.h>
#include <window/hud/optional_element.h>
#include <window/hud/group.h>
#include <window/hud/button.h>

#include <math/random/random_enums.h>

#include <functional>

namespace rpg {
using namespace rpg::hud;
using namespace math::random;
using math::random::RNG_Distribution;
using std::string;
using std::vector;

/*! \brief Used as a callback to create the required stuff for a random
 * distribution */
void ChangeRandomEngine(RandomOrConstant* roc) {
  printf(" CHANGE ENGINE \n");

  roc->set_generator(roc->next_algorithm);
}

/*! \brief Used as a callback to change the distribution a ROC is using */
void ChangeRandomDistribution(RandomOrConstant* roc) {
  printf("CHANGE DISTRIBUTION min:%f, max: %f\n", roc->rand_min, roc->rand_max);

  const RNG_Distribution next_distribution = roc->next_distribution;
  switch (next_distribution) {
    case RNG_Distribution::NORMAL:
      roc->set_distribution(new Normal(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::UNIFORM:
      roc->set_distribution(new Uniform(roc->rand_min, roc->rand_max));
      break;
  }
}

Widget* CreateDistributionWidgets(RandomOrConstant& ROC,
                                  const std::string& name) {
  int* distribution_ptr = reinterpret_cast<int*>(&ROC.next_distribution);
  int* engine_ptr = reinterpret_cast<int*>(&ROC.next_algorithm);

  const vector<string> distributions{"Uniform", "Normal"};

  const vector<string> engines = {"Default",  "MinSTD",     "MT19937",
                                  "Ranlux48", "Ranlux48_B", "Knuth"};

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
  Widget* mean_slider =
      new Slider("mean", &ROC.rand_min, ROC.min_value, ROC.max_value);
  Widget* std_slider =
      new Slider("standard_dev", &ROC.rand_max, ROC.min_value, ROC.max_value);
  Widget* distribution_pane = new MultiWidget(
      std::vector<Widget*>{min_slider, max_slider, mean_slider, std_slider},
      distribution_ptr, {{0, 1}, {2, 3}});

  Widget* constant_slider =
      new Slider(name, &ROC.constant, ROC.min_value, ROC.max_value);
  Widget* update_dist_button =
      new Button("Update Random Generator", "Update Random Genreator",
                 std::bind(ChangeRandomDistribution, &ROC));
  Widget* random_group =
      new Group("Random",
                vector<Widget*>{engine_select, distribution_select,
                                distribution_pane, update_dist_button},
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