#pragma once

#include <window/hud/multi_widget.h>
#include <window/hud/combo.h>
#include <random_or_constant.h>

namespace rpg {

/*! \brief Creates a multiwidget that will change to fit any distribution in
 * ROC*/
rpg::hud::Widget* CreateDistributionWidgets(RandomOrConstant& ROC,
                                            const std::string& name);

/*! \brief Update the distribution used by ROC */
void UpdateROC(RandomOrConstant* ROC);

}  // namespace rpg