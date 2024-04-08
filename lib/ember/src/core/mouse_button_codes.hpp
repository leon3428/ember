#ifndef MOUSE_BUTTON_CODES
#define MOUSE_BUTTON_CODES

// from glfw

namespace ember {
    enum class MouseButtonCode : short {
            MouseButtonLeft = 0,
            MouseButtonRight = 1,
            MouseButtonMiddle = 2,
            MouseButton4 = 3,
            MouseButton5 = 4,
            MouseButton6 = 5,
            MouseButton7 = 6,
            MouseButton8 = 7,
    };
}

#endif // MOUSE_BUTTON_CODES