
#ifndef FINITY_GUI_GFX_H
#define FINITY_GUI_GFX_H

#include <GLFW/glfw3.h>
#include <finPch.h>

enum class EInputButton {
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2,
    NONE = 9
};

class Input {
public:
    static EInputButton GetPressedButton(GLFWwindow *window) {
        EInputButton result = EInputButton::NONE;
        if (glfwGetMouseButton(window, 0)==GLFW_PRESS)
            return EInputButton::LEFT;
        else if (glfwGetMouseButton(window, 1)==GLFW_PRESS)
            return EInputButton::RIGHT;
        else if (glfwGetMouseButton(window, 2)==GLFW_PRESS)
            return EInputButton::MIDDLE;
        else
            return EInputButton::NONE;
    }
};

#endif //FINITY_GUI_GFX_H
