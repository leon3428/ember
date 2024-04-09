#include "window.hpp"

#include <stdexcept>

auto keyCallback(GLFWwindow *window, int key, int, int action, int mods) -> void {
  if (action == GLFW_PRESS) {
    auto pEventBus = static_cast<ember::EventBus *>(glfwGetWindowUserPointer(window));

    pEventBus->fire<ember::KeyPressedEvent>({static_cast<ember::KeyCode>(key), mods});
  }
}

auto mouseButtonCallback(GLFWwindow *window, int button, int action, int) -> void {
  if (action == GLFW_PRESS) {
    auto pEventBus = static_cast<ember::EventBus *>(glfwGetWindowUserPointer(window));

    pEventBus->fire<ember::MouseButtonPressedEvent>({static_cast<ember::MouseButtonCode>(button)});
  }
}

auto resizeCallback(GLFWwindow *window, int width, int height) -> void {
  auto pEventBus = static_cast<ember::EventBus *>(glfwGetWindowUserPointer(window));

  pEventBus->fire<ember::ResizeEvent>({width, height});
}

ember::Window::Window(std::string_view name, int width, int height) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to create the window.");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwSwapInterval(1);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_pWindow = glfwCreateWindow(width, height, name.data(), NULL, NULL);

  if (m_pWindow == nullptr) throw std::runtime_error("Failed to create the window.");

  glfwMakeContextCurrent(m_pWindow);
  glfwSetWindowUserPointer(m_pWindow, &m_eventBus);

  glfwSetKeyCallback(m_pWindow, keyCallback);
  glfwSetFramebufferSizeCallback(m_pWindow, resizeCallback);
  glfwSetMouseButtonCallback(m_pWindow, mouseButtonCallback);
}

ember::Window::~Window() {
  if (m_pWindow) {
    glfwDestroyWindow(m_pWindow);
    m_pWindow = nullptr;
  }
}

ember::Window::Window(Window &&other) {
  m_pWindow = other.m_pWindow;
  other.m_pWindow = nullptr;

  m_eventBus = std::move(other.m_eventBus);
}

auto ember::Window::operator=(Window &&other) -> Window & {
  if (this != &other) {
    if (m_pWindow != nullptr) glfwDestroyWindow(m_pWindow);

    m_pWindow = other.m_pWindow;
    other.m_pWindow = nullptr;

    m_eventBus = std::move(other.m_eventBus);
  }

  return *this;
}

auto ember::Window::isKeyPressed(KeyCode keyCode) const -> bool {
  auto state = glfwGetKey(m_pWindow, static_cast<int>(keyCode));
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

auto ember::Window::isMouseButtonPressed(MouseButtonCode mouseButtonCode) const -> bool {
  auto state = glfwGetMouseButton(m_pWindow, static_cast<int>(mouseButtonCode));
  return state == GLFW_PRESS;
}

auto ember::Window::getMousePos() const -> std::tuple<float, float> {
  double x, y;
  glfwGetCursorPos(m_pWindow, &x, &y);

  return {x, y};
}

auto ember::Window::getSize() const -> std::tuple<int, int> {
  int width, height;
  glfwGetWindowSize(m_pWindow, &width, &height);

  return {width, height};
}