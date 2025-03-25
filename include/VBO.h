#ifndef _VBO_H
#define _VBO_H

#include <glad/glad.h>

typedef struct s_VBO
{
	GLuint ID;
} VBO;

VBO* VBO_new(GLfloat* vertices, GLsizei size);
extern void VBO_free(VBO* vbo);

extern void VBO_Bind(VBO* vbo);
extern void VBO_Unbind(VBO* vbo);

#endif
