#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
float screenWidth;
float screenHeight;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float posXValue;
float posYValue;
const float vertexNum = 12.0f;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
/*
 *

float vertices[] = {
    // 0
    +0.0f, +0.0f,
    +1.0f, +0.0f, +0.0f,
    // 1
    +0.25f, +0.25f,
    +1.0f, +0.0f, +0.0f,
    // 2
    +0.0f, +0.5f,
    +0.0f, +1.0f, +0.0f,
    // 3
    -0.25f, 0.25f,
    +0.0f, +1.0f, +0.0f,

    // 4
    +0.25f, -0.25f,
    +0.0f, +0.0f, +1.0f,
    // 5
    +0.25f, -0.75f,
    +0.5f, +0.5f, +0.0f,
    // 6
    +0.75f, -0.75f,
    +0.5f, +0.0f, +0.5f,
    // 7
    +0.75f, -0.25f,
    +0.0f, +0.5f, +0.5f,

};
 */

// indices
GLushort indices[] = { 0,1,2, 3,0,2, 4,5,6, 7,4,5 };
