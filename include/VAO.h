#ifndef _VAO_H
#define _VAO_H

#include <glad/glad.h>
#include "VBO.h"

typedef struct s_VAO
{
	GLuint ID;
} VAO;

VAO* VAO_new();
extern void VAO_free(VAO* vao);

extern void VAO_LinkAttrib(VAO* vao, VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
extern void VAO_Bind(VAO* vao);
extern void VAO_Unbind(VAO* vao);

#endif
