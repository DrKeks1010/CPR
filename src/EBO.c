#include "EBO.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

EBO* EBO_new(GLuint* indices, GLsizeiptr size)
{
	EBO* ebo = malloc(sizeof(EBO));
	if (ebo == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create EBO!\n", sizeof(EBO));
		return NULL;
	}

	//Generate the EBO with 1 object
	glGenBuffers(1, &ebo->ID);

	EBO_bind(ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

	return ebo;
}
inline void EBO_free(EBO* ebo)
{
	glDeleteBuffers(1, &ebo->ID);
	free(ebo);
}

inline void EBO_bind(EBO* ebo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->ID);
}
inline void EBO_unbind(EBO* ebo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
