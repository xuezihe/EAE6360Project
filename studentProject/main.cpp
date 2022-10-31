#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gl/GL.h"
#include <iostream>
#include "stb_image.h"
#include "shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp""
#include "gtc/type_ptr.hpp"
#include "MyCamera.h"
#include "Primitives/ShapeGenerator.h"
#include "main.h"






int main()
{
	auto window = initwindow();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	// load shader
	Shader MyShader("shaders/test.vs", "shaders/test.fs");
	Shader lightShader("shaders/lighting.vs", "shaders/lighting.fs");

	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Create 1st Texture
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set default texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true); //flip
	// load 1st texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("img/img_1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// specify a two-dimensional texture image and generate mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// Create 2nd Texture
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// load 2nd texture
	data = stbi_load("img/test.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// specify a two-dimensional texture image and generate mipma
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// set uniform value
	MyShader.use();
	MyShader.setInt("Texture1", 0);
	MyShader.setInt("Texture2", 1);

	// bind texture to buffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);




	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------
	glm::mat4 projection = glm::perspective(glm::radians(fov), 800/600.0f, 0.1f, 100.0f);
	MyShader.setMat4("projection", projection);

	// draw loop
	while (!glfwWindowShouldClose(window))
	{


		// input 
		processInput(window);
		mouseMoveInput(window);

		// clear screen 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// be sure to activate shader when setting uniforms/drawing objects
		MyShader.use();
		MyShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		MyShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);



		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		view = camera.getWorldToViewMatrix();
		MyShader.setMat4("view", view);


		// draw 
		glm::mat4 model = glm::mat4(1.0f);
		MyShader.setMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);




		//swap buffers
		// glFlush();
		glfwSwapBuffers(window);
		// input
		glfwPollEvents();
	}
	// free
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(MyShader.ID);
	// glfw close
	glfwTerminate();
	return 0;
}
// viewport function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/// <summary>
/// mouse input function
/// </summary>
/// <param name="window"></param>
void mouseMoveInput(GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	camera.mouseUpdate(glm::vec2(xpos* mousespeed, ypos* mousespeed));
}


/// <summary>
/// keyboard input function
/// </summary>
/// <param name="window"></param>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.moveForward();

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.moveBackward();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.strafeLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.strafeRight();
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		camera.moveUp();
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		camera.moveDown();
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	yoffset = 5.0f;
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
GLFWwindow* initwindow()
{
	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create glfw windows
	GLFWwindow* window = glfwCreateWindow(800, 600, "01_Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// bind context with window
	glfwMakeContextCurrent(window);

	// glad callback
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	// resize window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	return window;
}



