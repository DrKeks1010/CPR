#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

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

  // Main window loop
  while (!glfwWindowShouldClose(window)) 
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    // Poll GLFW events
    glfwPollEvents();
  }

  // Close resources
  glfwDestroyWindow(window);
  glfwTerminate();

  printf("Project exited without any errors!\n");
  return 0;
}
