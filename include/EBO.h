#ifndef _EBO_H
#define _EBO_H

#include <glad/glad.h>

typedef struct s_EBO
{
	GLuint ID;
} EBO;

EBO* EBO_new(GLuint* indices, GLsizeiptr size);
extern void EBO_free(EBO* ebo);

extern void EBO_Bind(EBO* ebo);
extern void EBO_Unbind(EBO* ebo);

#endif
