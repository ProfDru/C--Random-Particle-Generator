#include <window/window.h>
#include <utils.h>
#include <window/hud_manager.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <cassert>
#include <exception>
#include <iostream>

namespace rpg {

/*! \brief Get the wrapper object for this window.

        \remarks This just allows for getting the window pointer and casting it
   with les verbosity
*/
rpg::Window* GetWindow(GLFWwindow* window) {
  return reinterpret_cast<rpg::Window*>(glfwGetWindowUserPointer(window));
}

/*! \brief Execute this window's resize callback, and resize it's viewport

        \todo Should this be calling glviewport?

*/
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  HudManager::WindowResizecallback(width, height);
  Globals::UpdateWindowSize(width, height);

  auto win = GetWindow(window);
  win->height = height;
  win->width = width;
  win->window_resize_callback(static_cast<float>(width),
                              static_cast<float>(height));
}

void WindowFocusCallback(GLFWwindow* window, int focused) {
  auto win = GetWindow(window);

  win->SetFocus(focused);
}

void MouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
  HudManager::MouseClickCallback(action, button);
}

/*! \brief Calls the window's callback and resets the mouse's position to
    the screen center

  \todo Update this to handle pausing
*/
void MouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
  HudManager::MousePosCallback(x_pos, y_pos);

  auto win = GetWindow(window);
  win->mouse_callback(x_pos, y_pos);
}

void KeyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  HudManager::KeyCallBack(key, mods);

  auto win = GetWindow(window);
  // Ignore repeats
  if (action == GLFW_REPEAT)
    return;
  const bool is_key_down = action == GLFW_PRESS;
  win->key_callback(is_key_down, key);
}

/*! \brief Called by glfw when there's an issue */
void ErrorCallBack(int, const char* err_str) {
  std::cerr << "] GLFW Error: " << err_str << std::endl;
}

/*! \brief Called by OpenGL when there's an error. */
void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const char* message,
                                const void* userParam) {
  // return;
  if (severity != 0x826b)
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
}

/*!
    \brief Initializes glew and prints an errof if one is found
    \returns false if GLEW couldn't be initialized, true if it could
*/
bool InitGlew() {
  auto glewinit_res = glewInit();
  if (glewinit_res != GLEW_OK) {
    fprintf(stderr, "Glew init error: %s\n", glewGetErrorString(glewinit_res));
    return false;
  }
  return true;
}

/*! \brief Initalize and return the glfw window*/
GLFWwindow* InitWindow(float window_width, float window_height) {
  printf("Initializing GLFW...\n");
  glewExperimental = true;

  // throw some exception if this cannot init (Should be an actual exception)
  if (!glfwInit())
    throw std::exception();

  // Create a new window, throw if it fails
  printf("Creating Window...\n");
  GLFWwindow* window = glfwCreateWindow(window_width, window_height,
                                        "Random Particle Engine", NULL, NULL);
  assert(window != NULL);

  // Set the new window as the current context
  glfwMakeContextCurrent(window);

  // Enable depth buffer test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);
  glDepthRange(0.0f, 1.0f);

  // Enable several opengl settings
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_POINT_SPRITE);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  // Make the window resizable and update at 60 FPS
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_REFRESH_RATE, 120);
  glfwWindowHint(GLFW_SAMPLES, 16);
  glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_BLEND);
  printf("Initializing GLEW...\n");
  bool did_init = InitGlew();
  assert(did_init);

  printf("Returning Window...\n");
  return window;
}

void EnableDebugging(GLFWwindow* win) {
  // Setup the error callback for GLFW
  glfwSetErrorCallback(ErrorCallBack);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
}

void Window::SetFocus(bool new_focus) {
  this->has_focus = new_focus;
  UpdateTracking();
}

void Window::TrackMouse(bool should_track) {
  if (this->track_mouse != should_track) {
    this->track_mouse = should_track;
    UpdateTracking();
  }
}

void Window::UpdateTracking() {
  bool should_capture = this->has_focus && this->track_mouse;
  window_focused_callback(should_capture);
  CaptureMouse(should_capture);
}

void Window::CaptureMouse(bool should_capture) {
  auto input_mode = should_capture ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL;

  HudManager::SetEnabled(!should_capture);
  glfwSetInputMode(this->win, GLFW_CURSOR, input_mode);
}

void Window::SetKeyCallback(std::function<void(bool, int)> func) {
  this->key_callback = func;
}

/*! \brief Set the callback function for when inputs are updated*/
void Window::SetResizeCallback(std::function<void(float, float)> func) {
  this->window_resize_callback = func;
}

/*! \brief Set the callback for when the mouse is moved */
void Window::SetMouseCallback(std::function<void(float, float)> func) {
  this->mouse_callback = func;
}

/*! \brief Set the callback for when the mouse is moved */
void Window::SetWindowFocusCallback(std::function<void(bool)> func) {
  this->window_focused_callback = func;
}

void Window::Init(float width, float height) {
  this->width = width;
  this->height = height;
  this->win = InitWindow(width, height);
  HudManager::Init(this->win);

  EnableDebugging(this->win);
  CaptureMouse(true);

  glfwSetWindowUserPointer(this->win, this);

  glClearColor(this->clear_color[0], this->clear_color[1], this->clear_color[2],
               1);

  // Setup callbacks
  glfwSetFramebufferSizeCallback(win, FramebufferSizeCallback);
  glfwSetCursorPosCallback(win, MouseCallback);
  glfwSetKeyCallback(win, KeyCallback);
  glfwSetWindowFocusCallback(win, WindowFocusCallback);
  glfwSetMouseButtonCallback(win, MouseClickCallback);
}

void Window::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::UpdateSize() {
  FramebufferSizeCallback(this->win, this->width, this->height);
}

bool Window::Redraw() {
  HudManager::Draw();

  glfwSwapBuffers(this->win);
  glfwPollEvents();

  const auto screen_center = Globals::ScreenCenter();

  if (this->has_focus && this->track_mouse)
    glfwSetCursorPos(this->win, screen_center.x, screen_center.y);

  //! \todo Handle this with controls
  return glfwGetKey(this->win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(this->win) == 0;
}

}  // namespace rpg