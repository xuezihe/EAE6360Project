#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
float screenWidth;
float screenHeight;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);