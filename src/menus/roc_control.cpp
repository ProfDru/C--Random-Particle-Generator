#include <menus/roc_control.h>

#include <random>

#include <math/random/distribution.h>
#include <math/random/distributions/normal.h>
#include <math/random/distributions/uniform.h>
#include <math/random/distributions/log_normal.h>
#include <math/random/distributions/general.h>

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
  roc->set_generator(roc->next_algorithm);
}

/*! \brief Used as a callback to change the distribution a ROC is using  and the
 * names/ranges of each slider. */
void ChangeRandomDistribution(RandomOrConstant* roc,
                              Slider* slider_1,
                              Slider* slider_2,
                              Slider* scale_slider) {
  const RNG_Distribution next_distribution = roc->next_distribution;
  std::array<std::string, 2> slider_names = {"", ""};

  // If this is set to true in the case statment, then the slider's parameters
  // will be capped beetween 0 and 1, and the ROC will apply its scale factor
  // to all produced values
  bool normalized_scale = false;

  // Change behavior based on which distribution type is selected.
  switch (next_distribution) {
    case RNG_Distribution::NORMAL:
      slider_names = {"Mean", "Standard Deviation"};
      roc->set_distribution(new Normal(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::UNIFORM:
      slider_names = {"min", "max"};
      roc->set_distribution(new Uniform(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::LOG_NORMAL:
      slider_names = {"Log Mean", "Log Deviation"};
      roc->set_distribution(new LogNormal(roc->rand_min, roc->rand_max));
      normalized_scale = true;
      break;
    case RNG_Distribution::EXTREME:
      slider_names = {"Location", "Scale"};
      roc->set_distribution(
          new ExtremeDistribution(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::WEIBULL:
      slider_names = {"a", "b"};
      roc->set_distribution(
          new WeibullDistribution(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::CHI:
      slider_names = {"Degrees of Freedom", ""};
      roc->set_distribution(new ChiSquaredDistribution(roc->rand_min));
      break;
    case RNG_Distribution::STUDENT:
      slider_names = {"Degrees of Freedom", ""};
      normalized_scale = true;
      roc->set_distribution(new StudentDistribution(roc->rand_min));
      break;
    case RNG_Distribution::FISHER:
      slider_names = {"m", "n"};
      normalized_scale = true;
      roc->set_distribution(
          new FisherDistribution(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::GAMMA:
      slider_names = {"alpha", "beta"};
      roc->set_distribution(
          new GammaDistribution(roc->rand_min, roc->rand_max));
      break;
    case RNG_Distribution::EXPONENTIAL:
      slider_names = {"lambda", ""};
      normalized_scale = true;
      roc->set_distribution(new ExponentialDistribution(roc->rand_min));
      break;
  }

  // Update the labels for sliders 1 and 2
  slider_1->text = slider_names[0];
  slider_2->text = slider_names[1];

  // Either set the slider's bounds to the ROC's maximum and minimum random
  // values or between 1 and 0
  if (!normalized_scale) {
    slider_1->min = roc->min_value;
    slider_1->max = roc->max_value;

    slider_2->min = roc->min_value;
    slider_2->max = roc->max_value;
    roc->scale_factor = 1;
  } else {
    slider_1->min = 0;
    slider_1->max = 1;
    slider_2->min = 0;
    slider_2->max = 1;

    scale_slider->min = roc->min_value;
    scale_slider->max = roc->max_value;
  }
}

/*! \brief Create a group of widgets to control a ROC.

  \details This uses std::bind to create void function pointers with ROCs and
  sliders as arguments to ChangeRandomDistribution and ChangeRandomEngine.

 */
Widget* CreateDistributionWidgets(RandomOrConstant& ROC,
                                  const std::string& name) {
  // THis must be ordered to match up with the order of enums in
  // RNG_Distribution
  const vector<string> distributions{
      "Uniform", "Normal",  "LogNormal", "Extreme", "Weibull",
      "Chi",     "Student", "Fisher",    "Gamma",   "Exponential"};

  // THis must be ordered to match up with the order of enums in RNG_Algorithm
  const vector<string> engines = {"Default",  "MinSTD",     "MT19937",
                                  "Ranlux48", "Ranlux48_B", "Knuth"};

  int* distribution_ptr = reinterpret_cast<int*>(&ROC.next_distribution);
  int* engine_ptr = reinterpret_cast<int*>(&ROC.next_algorithm);

  Widget* random_toggle = new CheckBox("Use random?", &ROC.use_random);
  Widget* engine_select = new ComboBox("Random Engine", engines, engine_ptr,
                                       std::bind(ChangeRandomEngine, &ROC));

  Slider* min_slider =
      new Slider("min", &ROC.rand_min, ROC.min_value, ROC.max_value);
  Slider* max_slider =
      new Slider("max", &ROC.rand_max, ROC.min_value, ROC.max_value);
  Slider* scale_slider =
      new Slider("scale", &ROC.scale_factor, ROC.min_value, ROC.max_value);

  auto update_dist_function = std::bind(ChangeRandomDistribution, &ROC,
                                        min_slider, max_slider, scale_slider);

  Widget* distribution_select = new ComboBox(
      "Distribution", distributions, distribution_ptr, update_dist_function);

  max_slider->SetReleaseCallback(update_dist_function);
  min_slider->SetReleaseCallback(update_dist_function);

  // This determines which widgets are drawn for each value in distributions in
  // order.
  Widget* distribution_pane = new MultiWidget(
      std::vector<Widget*>{min_slider, max_slider, scale_slider},
      distribution_ptr,
      {{0, 1},
       {0, 1},
       {0, 1, 2},
       {0, 1},
       {0, 1},
       {0},
       {0, 2},
       {0, 1, 2},
       {0, 1},
       {0, 2}});

  Widget* constant_slider =
      new Slider(name, &ROC.constant, ROC.min_value, ROC.max_value);
  Widget* random_group = new Group(
      "Random",
      vector<Widget*>{engine_select, distribution_select, distribution_pane},
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