#include <window/hud_manager.h>

#include <AntTweakBar.h>
namespace rpg {

void HudManager::SetParam(const std::string& param, const std::string& val) {
  std::string param_string =
      " " + HudManager::name + " " + param + "=" + val + " ";

  TwDefine(param_string.c_str());
}

void HudManager::Init(float window_x, float window_y) {
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(window_x, window_y);
  HudManager::main_bar = TwNewBar(name.c_str());

  SetParam("visible", "true");
  SetParam("position", "'0 0'");
  SetParam("size", "'120, 280'");
  SetParam("label", "FirstWindow");
}

void HudManager::Draw() {
  TwDraw();
}

bool HudManager::KeyCallBack(int key, int mods) {
  return TwKeyPressed(key, mods);
}

bool HudManager::MouseClickCallback(int mouse_action, int mouse_button) {
  return TwMouseButton(static_cast<TwMouseAction>(mouse_action),
                       static_cast<TwMouseButtonID>(mouse_button));
}
bool HudManager::MousePosCallback(int mouseX, int mouseY) {
  return TwMouseMotion(mouseX, mouseY);
}
bool HudManager::ScrollWheelCallback(int pos) {
  return TwMouseWheel(pos);
}
bool HudManager::WindowResizecallback(int width, int height) {
  TwWindowSize(width, height);

  //! \todo Can't find the function for this right now
  return true;
}

}  // namespace rpg