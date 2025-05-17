#ifndef _EBO_H
#define _EBO_H

#include <glad/glad.h>

typedef struct s_EBO
{
	GLuint ID;
} EBO;

EBO* EBO_new(GLuint* indices, GLsizeiptr size);
void EBO_free(EBO* ebo);

void EBO_bind(EBO* ebo);
void EBO_unbind(EBO* ebo);

#endif
