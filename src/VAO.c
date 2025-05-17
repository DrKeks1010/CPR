#include "VAO.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

VAO* VAO_new()
{
	VAO* vao = malloc(sizeof(VAO));
	if (vao == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create VAO!\n", sizeof(VAO));
		return NULL;
	}

	//Generate the VAO with 1 object
	glGenVertexArrays(1, &vao->ID);

	return vao;
}
inline void VAO_free(VAO* vao)
{
	glDeleteVertexArrays(1, &vao->ID);
	free(vao);
}

inline void VAO_linkAttrib(VAO* vao, VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO_bind(vbo);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the Vertex Attribut so that OPENGL knows to use it
	glEnableVertexAttribArray(layout);

	VBO_unbind(vbo);
}
inline void VAO_bind(VAO* vao)
{
	glBindVertexArray(vao->ID);
}
inline void VAO_unbind(VAO* vao)
{
	glBindVertexArray(0);
}
