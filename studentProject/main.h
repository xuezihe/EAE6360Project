#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float mousespeed = 0.01f;
float fov = 45.0f;

//init 
const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
GLuint theBufferID;
GLuint cube1IndexByteOffset;
GLuint cube2IndexByteOffset;
GLuint arrowIndexByteOffset;
GLuint triangleIndexByteOffset;

GLuint cube1NumIndices;
GLuint cube2NumIndices;
GLuint arrowNumIndices;
GLuint triangleNumIndices;

GLuint cube1VertexArrayObjectID;
GLuint cube2VertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint triangleVertexArrayObjectID;
// declare functions
GLFWwindow* initwindow();
void mouseMoveInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// load camera
Camera camera;



// lighting
glm::vec3 lightPos(0.0f, 3.0f, 0.0f);
