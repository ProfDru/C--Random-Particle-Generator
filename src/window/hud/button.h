#pragma once

#include <window/hud/widget.h>
#include <window/hud/label.h>

#include <functional>

namespace rpg::hud {

/*! \brief A simple button that will set a given boolean to true  */
class Button : public Label {
 public:
  /*! \brief The mode of operation for a button */
  enum class MODE { ONE_FRAME, CONSTANT };
  std::function<void()>
      press_function;  //< Function to call when the button is pressed

 private:
  bool was_pressed_last_frame;  //< Set to true if the boutton was pressed last
                                // frame
  MODE mode;

 public:
  /*! \brief  Construct a new button

    \see MODE for a list of button modes and their behaviors
  */
  Button(const std::string& name,
         const std::string& text,
         std::function<void()> press_function,
         MODE mode = MODE::ONE_FRAME);

  void Draw() override;
  ~Button(){};
};
}  // namespace rpg::hud