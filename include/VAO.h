#ifndef _VAO_H
#define _VAO_H

#include <glad/glad.h>
#include "VBO.h"

typedef struct s_VAO
{
	GLuint ID;
} VAO;

VAO* VAO_new();
void VAO_free(VAO* vao);

void VAO_linkAttrib(VAO* vao, VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
void VAO_bind(VAO* vao);
void VAO_unbind(VAO* vao);

#endif
