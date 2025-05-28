#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "Chunk.h"

Chunk* Chunk_new(GLfloat* vertices, GLsizei verticesSize, GLuint* indices, GLsizei indicesSize, GLsizei indicesCount)
{
	Chunk* chunk = calloc(1, sizeof(Chunk));
	if (chunk == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create Chunk!\n", sizeof(Chunk));
	}

	chunk->indicesCount = indicesCount;
	
	if ((chunk->vao = VAO_new()) == NULL)
	{
		fputs("Failed to create Vertex Array Object in Chunk!\n", stderr);
		Chunk_free(chunk);
		return NULL;
	}

	if ((chunk->vbo = VBO_new(vertices, verticesSize)) == NULL)
	{
		fputs("Failed to create Vertex Buffer Object in Chunk!\n", stderr);
		VAO_unbind(chunk->vao);
		Chunk_free(chunk);
		return NULL;
	}

	if ((chunk->ebo = EBO_new(indices, indicesSize)) == NULL)
	{
		fputs("Failed to create Element Buffer Object!\n", stderr);
		VBO_unbind(chunk->vbo);
		VAO_unbind(chunk->vao);
		Chunk_free(chunk);
		return NULL;
	}

	VAO_linkAttrib(chunk->vao, chunk->vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)(0));
	VAO_unbind(chunk->vao);
	VBO_unbind(chunk->vbo);
	EBO_unbind(chunk->ebo);

	return chunk;
}
inline void Chunk_free(Chunk* chunk)
{
	if (chunk->vao) VAO_free(chunk->vao);
	if (chunk->vbo) VBO_free(chunk->vbo);
	if (chunk->ebo) EBO_free(chunk->ebo);

	free(chunk);
}

inline void Chunk_draw(Chunk* chunk)
{
	VAO_bind(chunk->vao);
	glDrawElements(GL_TRIANGLE_STRIP, chunk->indicesCount, GL_UNSIGNED_INT, 0);
}

Chunk* Chunk_generate()
{
		// Vertices coordinates
	GLfloat s_vertices[] =
	{
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
	};
	GLfloat* vertices = malloc(sizeof(s_vertices));
	memcpy(vertices, s_vertices, sizeof(s_vertices));
	GLuint s_indices[] =
	{
		0, 2, 1, 3
	};
	GLuint* indices = malloc(sizeof(s_indices));
	memcpy(indices, s_indices, sizeof(s_indices));

	return Chunk_new(vertices, sizeof(s_vertices), indices, sizeof(s_indices), 4);
}
