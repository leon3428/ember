#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string_view>
#include "event_bus.hpp"
#include "key_codes.hpp"
#include "mouse_button_codes.hpp"

namespace ember {

// TODO: improve events
struct KeyPressedEvent {
  constexpr static auto idn = "KeyPressedEvent"_id;
  KeyCode keyCode;
  int mods;
};

struct MouseButtonPressedEvent {
  constexpr static auto idn = "MouseButtonPressedEvent"_id;
  MouseButtonCode keyCode;
};

struct ResizeEvent {
  constexpr static auto idn = "ResizeEvent"_id;
  int width;
  int height;
};

auto scrollCallback(GLFWwindow *window, double, double yOffset) -> void;

class Window {
 public:
  inline Window() { Window("Ember", 800, 600); };
  Window(std::string_view name, int width, int height);

  ~Window();

  Window(const Window &) = delete;
  auto operator=(const Window &) -> Window & = delete;

  Window(Window &&);
  auto operator=(Window &&) -> Window &;

  [[nodiscard]] inline auto shouldClose() const -> bool { return glfwWindowShouldClose(m_pWindow); }

  inline auto update() const -> void {
    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
  }

  [[nodiscard]] inline auto getEventBus() -> EventBus & { return m_eventBus; }

  [[nodiscard]] auto isKeyPressed(KeyCode keyCode) const -> bool;
  [[nodiscard]] auto isMouseButtonPressed(MouseButtonCode mouseButtonCode) const -> bool;
  [[nodiscard]] auto getMousePos() const -> std::tuple<float, float>;
  [[nodiscard]] auto getSize() const -> std::tuple<int, int>;
  [[nodiscard]] inline auto getScrollDist() const { return m_scrollDist; }


  friend auto scrollCallback(GLFWwindow *, double, double) -> void;

 private:
  unsigned m_scrollDist;

  GLFWwindow *m_pWindow;
  EventBus m_eventBus;
};


}  // namespace ember

#endif  // WINDOW_HPP