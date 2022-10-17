#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gl/GL.h"
#include <iostream>
#include "stb_image.h"
#include "shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp""
#include "gtc/type_ptr.hpp"

// Declare function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void drawHUD();
void mytriangle();
Shader pretriangle();

// global variables
bool Myswitch = 0;
//vertex array cubes
float vertices[] = { // 36 vertex, xyz,uv

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// several cubes location
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
};

// triangle vertex array
float triangleVertices[]=
{
   -0.1f, -0.1f, 0.0f,
	1.0f, -0.1f, 0.0f,
	0.0f,  0.1f, 0.0f
};
//vertex index
unsigned int indices[] = { 
	0, 1, 2, 
	1, 2, 3  
};


int main()
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
		return -1;
	}
	// bind context with window
	glfwMakeContextCurrent(window);

	// glad callback
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// resize window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load shader
	Shader MyShader("shaders/test.vs", "shaders/test.fs");
	// MyShader.use();

	//load second shader
	Shader triangleShader = pretriangle();

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


	// Create 3rd Texture
	unsigned int texture3;
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	// load 3rd texture
	data = stbi_load("img/Doraemon_small.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// specify a two-dimensional texture image and generate mipma
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load the third texture" << std::endl;
	}
	stbi_image_free(data);

	// bind texture to buffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);

	// set uniform value
	MyShader.setInt("ourTexture1", 0);
	MyShader.setInt("ourTexture2", 1);
	MyShader.setInt("ourTexture3", 2);
	// gen VBO buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// gen EBO index data
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//gen VAO attribute 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// bind VAO
	glBindVertexArray(VAO);
	// bind VBO，send vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//bind EBO
	/*
	 *	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	 */

	// set vertex description
	// 0 for xyz, 1 for uv totally 5
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// draw loop
	while (!glfwWindowShouldClose(window))
	{
		// input 
		processInput(window);

		// Depth test
		glEnable(GL_DEPTH_TEST);

		// clear screen 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

		// setup for 3d new 
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		// gluPerspective(40.0, (GLdouble)800 / (GLdouble)600, 0.5, 20.0);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

		// draw 
		// draw several cubes
		for (int i = 0; i < 3; i++)
		{
			MyShader.use();
				// model matrix 
				glm::mat4 model(1.0f);
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, (float)glfwGetTime()* glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				// view matrix (move camera)
				glm::mat4 view(1.0f);
				view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
				// projection matrix 
				glm::mat4 projection(1.0f);
				projection = glm::perspective(glm::radians(50.0f), 800 / 600.0f, 0.01f, 1000.0f);
				// get index for model
				int modelLoc = glGetUniformLocation(MyShader.ID, "model");
				// set model uniform to shader
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				// get index for view
				int viewLoc = glGetUniformLocation(MyShader.ID, "view");
				// set view uniform to shader
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				// get index for projection 
				int projectionLoc = glGetUniformLocation(MyShader.ID, "projection");
				// set projection uniform to shader
				glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
				// draw 
				glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		triangleShader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*
		 *
		 * for only one cube
		glm::mat4 model(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(50.0f), 800 / 600.0f, 0.01f, 1000.0f);
		int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		 *
		 */

		/*
		 * for trans only
		 * glm::mat4 trans(1.0f);
		 * trans = glm::translate(trans, glm::vec3(0.0f, -0.3f, 0.0f));
		 * trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.1f));
		 * unsigned int transformLoc = glGetUniformLocation(MyShader.ID, "transform");
		 * glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		 * lDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
		 *
		 */
		// draw
		// glDrawArrays(GL_TRIANGLES, 0, 36);


		//swap buffers
		// glFlush();
		glfwSwapBuffers(window);
		// input
		glfwPollEvents();
	}
	// free
	glDeleteVertexArrays(1, &VAO);
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
// input 
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		switch (Myswitch)
		{
		case 1:
			Myswitch = 0;
		case 0:
			Myswitch = 1;
		}
	}
}

void drawHUD()
{
	/*
	 *
	 */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 800, 600, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, 10.0);
	glVertex2f(0.0, 10.0);
	glEnd();


	if (Myswitch)
	{
		// load HUD()
		// pre triangle
		pretriangle();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);



}

void mytriangle(Shader shader)
{
	// load triangle shader 
	
	shader.use();
}

Shader pretriangle()
{
	Shader TriangleShader("shaders/triangle.vs", "shaders/triangle.fs");

	return TriangleShader;
	

}

