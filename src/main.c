#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#include "linmath.h"
#include "timer.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define _WINDOW_NAME "OpenGL"

float WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
mat4x4 VIEW_MATRIX = mat4x4_identity(), PROJECTION_MATRIX = mat4x4_identity();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(void) 
{
	// Init glfw
	glfwInit();
	// Set glfw hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, _WINDOW_NAME, NULL, NULL);
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
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Enable face culling
	// glEnable(GL_CULL_FACE);
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

	// Create uniform to control rendering of object
	GLuint modelMatrixID = glGetUniformLocation(defaultShader->ID, "model");
	GLuint viewMatrixID = glGetUniformLocation(defaultShader->ID, "view");
	GLuint projectionMatrixID = glGetUniformLocation(defaultShader->ID, "projection");

	mat4x4 modelMatrix = mat4x4_identity();
	mat4x4_translate3f(VIEW_MATRIX, 0.f, 0.f, -1.5f);
	mat4x4_projection(PROJECTION_MATRIX, 90, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 1000);

	// Main window loop
	while (!glfwWindowShouldClose(window))
	{
		TIMER_UPDATE();
		processInput(window);
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader_Activate(defaultShader);
		// Set uniforms
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, VIEW_MATRIX);
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, PROJECTION_MATRIX);
		// bind the VAO so OpenGL knows to use it
		VAO_Bind(VAO1);
		// Draw the triangle using GL_TRIANGLE_STRIP primitive
		glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	mat4x4_projection(PROJECTION_MATRIX, 90, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 1000);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, 0.f, 0.f, TIMER_DELTA);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, 0.f, 0.f, -TIMER_DELTA);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, TIMER_DELTA, 0.f, 0.f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, -TIMER_DELTA, 0.f, 0.f);
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, 0.f, -TIMER_DELTA, 0.f);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		mat4x4_translate3f(VIEW_MATRIX, 0.f, TIMER_DELTA, 0.f);
}

