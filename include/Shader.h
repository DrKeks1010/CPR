#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct s_Shader 
{
	GLuint ID;
} Shader;

Shader* Shader_new(const char* vertexFile, const char* fragmentFile);
extern void Shader_free(Shader* sha);

extern void Shader_Activate(Shader* sha);

#endif
