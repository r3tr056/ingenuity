// feature_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <GLFW/glfw3.h>

int main()
{   
    std::cout << "Hello World!\n";
    GLFWwindow* window = glfwCreateWindow(600, 600, "Feature Test", glfwGetPrimaryMonitor(), nullptr);
    getchar();
    glfwDestroyWindow(window);
    return 0;
}

