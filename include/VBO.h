#ifndef _VBO_H
#define _VBO_H

#include <glad/glad.h>

typedef struct s_VBO
{
	GLuint ID;
} VBO;

VBO* VBO_new(GLfloat* vertices, GLsizei size);
void VBO_free(VBO* vbo);

void VBO_bind(VBO* vbo);
void VBO_unbind(VBO* vbo);

#endif
