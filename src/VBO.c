#include "VBO.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

VBO* VBO_new(GLfloat* vertices, GLsizei size)
{
	VBO* vbo = malloc(sizeof(VBO));
	if (vbo == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create VBO!\n", sizeof(VBO));
		return NULL;
	}

	//Generate the VBO with 1 object
	glGenBuffers(1, &vbo->ID);

	VBO_bind(vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	return vbo;
}
inline void VBO_free(VBO* vbo) 
{
	glDeleteBuffers(1, &vbo->ID);
	free(vbo);
}

inline void VBO_bind(VBO* vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
}
inline void VBO_unbind(VBO* vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
