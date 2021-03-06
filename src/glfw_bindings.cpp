#include <glfw_bindings.h>

#include <glfw/glfw3.h>

namespace rpg::input {

Bindings GLFW_binds::binds = Bindings({{GLFW_KEY_W, ACTION::FORWARD},
                                       {GLFW_KEY_A, ACTION::LEFT},
                                       {GLFW_KEY_S, ACTION::BACKWARD},
                                       {GLFW_KEY_D, ACTION::RIGHT},
                                       {GLFW_KEY_R, ACTION::RESET},
                                       {GLFW_KEY_SPACE, ACTION::UP},
                                       {GLFW_KEY_E, ACTION::UP},
                                       {GLFW_KEY_Q, ACTION::DOWN},
                                       {GLFW_KEY_LEFT_CONTROL, ACTION::BRAKE},
                                       {GLFW_KEY_LEFT_SHIFT, ACTION::BOOST},
                                       {GLFW_KEY_GRAVE_ACCENT, ACTION::PAUSE}});
}