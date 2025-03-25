#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define _WINDOW_WIDTH 800
#define _WINDOW_HEIGHT 800
#define _WINDOW_NAME "OpenGL"

int main(void) 
{
	// Init glfw
	glfwInit();
	// Set glfw hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] =
	{
		0, 1, 2, 3, 6, 0, 4, 1, 5, 3, 7, 6, 5, 4
	};



	// Create glfw window
	GLFWwindow* window = glfwCreateWindow(_WINDOW_WIDTH, _WINDOW_HEIGHT, _WINDOW_NAME, NULL, NULL);
	if (window == NULL)
	{
		perror(NULL);
		fputs("Failed to create GLFW window!\n", stderr);
		glfwTerminate();
		exit(-1);
	}
	// Get window context
	glfwMakeContextCurrent(window);

	// Load necessary opengl methods
	gladLoadGL();

	// Set the opengl viewport
	glViewport(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT);
	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Create shader
	Shader* defaultShader = Shader_new("resources/shaders/default.vert", "resources/shaders/default.frag");
	if (defaultShader == NULL)
	{
		fputs("Failed to create default Shader!\n", stderr);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	// Create VAO
	VAO* VAO1 = VAO_new();
	if (VAO1 == NULL)
	{
		fputs("Failed to create Vertex Array Object!\n", stderr);
		Shader_free(defaultShader);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}
	VAO_Bind(VAO1);

	// Create VBO
	VBO* VBO1 = VBO_new(vertices, sizeof(vertices));
	if (VBO1 == NULL)
	{
		fputs("Failed to create Vertex Buffer Object!\n", stderr);
		VAO_Unbind(VAO1);
		VAO_free(VAO1);
		Shader_free(defaultShader);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	// Create EBO
	EBO* EBO1 = EBO_new(indices, sizeof(indices));
	if (EBO1 == NULL)
	{
		fputs("Failed to create Element Buffer Object!\n", stderr);
		VBO_Unbind(VBO1);
		VBO_free(VBO1);
		VAO_Unbind(VAO1);
		VAO_free(VAO1);
		Shader_free(defaultShader);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	// Link VAO to VBO
	VAO_LinkAttrib(VAO1, VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(0));
	VAO_LinkAttrib(VAO1, VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind objects
	VAO_Unbind(VAO1);
	VBO_Unbind(VBO1);
	EBO_Unbind(EBO1);

	// Create uniform to control scale of object
	GLuint uniID = glGetUniformLocation(defaultShader->ID, "scale");

	// Main window loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Shader_Activate(defaultShader);
		// Set uniform
		glUniform1f(uniID, 1.5f);
		// bind the VAO so OpenGL knows to use it
		VAO_Bind(VAO1);
		// Draw the triangle using the GL_TRIANGELS primitive
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Poll GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO_free(VAO1);
	VBO_free(VBO1);
	EBO_free(EBO1);

	// Delete Shader
	Shader_free(defaultShader);

	// Close resources
	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Project exited without any errors!\n");
	return 0;
}
