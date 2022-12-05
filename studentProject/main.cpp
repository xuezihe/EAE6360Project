#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gl/GL.h"
#include <iostream>
#include "stb_image.h"
#include "shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "MyCamera.h"
#include "Primitives/ShapeGenerator.h"
#include "main.h"




int main()
{
	auto window = initwindow();
	ShapeData cube1 = ShapeGenerator::makeCube();
	ShapeData cube2 = ShapeGenerator::makeCube();
	ShapeData arrow = ShapeGenerator::makeArrow();
	ShapeData triangle = ShapeGenerator::makeTriangle();

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	// load shader
	Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
	// for white box
	Shader lightCubeShader("shaders/test.vs", "shaders/test.fs");
	//init 
	glGenBuffers(1, &theBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		cube1.vertexBufferSize() + cube1.indexBufferSize() +
		cube2.vertexBufferSize() + cube2.indexBufferSize() +
		arrow.vertexBufferSize() + arrow.indexBufferSize() +
		triangle.vertexBufferSize() + triangle.indexBufferSize(), 0, GL_STATIC_DRAW);
	GLsizeiptr currentOffset = 0;
	// cube1 
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube1.vertexBufferSize(), cube1.vertices);
	currentOffset += cube1.vertexBufferSize();
	cube1IndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube1.indexBufferSize(), cube1.indices);
	currentOffset += cube1.indexBufferSize();
	// cube2 
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube2.vertexBufferSize(), cube2.vertices);
	currentOffset += cube2.vertexBufferSize();
	cube2IndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube2.indexBufferSize(), cube2.indices);
	currentOffset += cube2.indexBufferSize();
	// arrow
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), cube2.vertices);
	currentOffset += arrow.vertexBufferSize();
	arrowIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), cube2.indices);
	currentOffset += arrow.indexBufferSize();
	// triangle
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, triangle.vertexBufferSize(), cube2.vertices);
	currentOffset += triangle.vertexBufferSize();
	triangleIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, triangle.indexBufferSize(), cube2.indices);
	currentOffset += triangle.indexBufferSize();

	// number indices
	cube1NumIndices = cube1.numIndices;
	std::cout << cube1NumIndices << std::endl;
	cube2NumIndices = cube2.numIndices;
	arrowNumIndices = arrow.numIndices;
	std::cout << arrowNumIndices << std::endl;

	triangleNumIndices = triangle.numIndices;

	glGenVertexArrays(1, &cube1VertexArrayObjectID);
	glGenVertexArrays(1, &cube2VertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);
	glGenVertexArrays(1, &triangleVertexArrayObjectID);

	glBindVertexArray(cube1VertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(cube2VertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint cubeByteOffset = cube1.vertexBufferSize() + cube1.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)cubeByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cubeByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cubeByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowByteOffset = cubeByteOffset + cube2.vertexBufferSize() + cube2.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(triangleVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint triangleByteOffset = arrowByteOffset+ arrow.vertexBufferSize() + arrow.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)triangleByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(triangleByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(triangleByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	/*
	cube1.cleanup();
	cube2.cleanup();
	arrow.cleanup();
	triangle.cleanup();
	*/


	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------
	glm::mat4 projection = glm::perspective(glm::radians(fov), 800/600.0f, 0.1f, 100.0f);
	lightCubeShader.setMat4("projection", projection);

	// draw loop
	while (!glfwWindowShouldClose(window))
	{

		// input 
		processInput(window);
		mouseMoveInput(window);

		// clear screen 
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);


		//camera
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getWorldToViewMatrix();
		// glm::mat4 worldToProjectionMatrix = projection * view;


		// draw cube1 
		glBindVertexArray(cube1VertexArrayObjectID);
		lightingShader.use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightPos", lightPos);
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		lightingShader.setVec3("viewPos", camera.getviewPostion());
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		lightingShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, cube1NumIndices, GL_UNSIGNED_SHORT, (void*)cube1IndexByteOffset);

		// draw cube2 
		glBindVertexArray(cube2VertexArrayObjectID);
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, cube2NumIndices, GL_UNSIGNED_SHORT, (void*)cube2IndexByteOffset);

		//draw arrow
		glBindVertexArray(arrowVertexArrayObjectID);
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f));
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexByteOffset);




		//swap buffers
		// glFlush();
		glfwSwapBuffers(window);
		// input
		glfwPollEvents();
	}
	// free
	glDeleteVertexArrays(1, &cube2VertexArrayObjectID);
	glDeleteBuffers(1, &theBufferID);
    glDeleteVertexArrays(1, &cube1VertexArrayObjectID);
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
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.moveUp();
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.moveDown();
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		lightPos.y +=0.1;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		lightPos.y -= 0.1;
	}	
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		lightPos.x += 0.1;
	}	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		lightPos.x -= 0.1;
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
	GLFWwindow* window = glfwCreateWindow(1200, 700, "MyOpenGL", NULL, NULL);
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



