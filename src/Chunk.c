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
		return NULL;
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

#define CHUNK_RESOLUTION 16
#define CHUNK_VERTICES_SIZE (sizeof(GLfloat) * (CHUNK_RESOLUTION + 1) * (CHUNK_RESOLUTION + 1) * 3)
#define CHUNK_INDICES_COUNT ((CHUNK_RESOLUTION + 1) * CHUNK_RESOLUTION * 2)
#define CHUNK_INDICES_SIZE (sizeof(GLuint) * CHUNK_INDICES_COUNT)

Chunk* Chunk_generate(vec2 from, vec2 to)
{
	GLfloat *vertices = malloc(CHUNK_VERTICES_SIZE);
	if (vertices == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create vertices array!\n", CHUNK_VERTICES_SIZE);
		return NULL;
	}
	GLuint* indices = malloc(CHUNK_INDICES_SIZE);
	if (indices == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create indices array!\n", CHUNK_INDICES_SIZE);
		free(vertices);
		return NULL;
	}

	size_t x, z, z_index, idx = 0;
	GLfloat x_pos, z_pos;
	vec2_sub(to, from);
	vec2_mulf(to, 1.0f / CHUNK_RESOLUTION);

	for (z = 0; z <= CHUNK_RESOLUTION; z++)
	{
		z_pos = from[1] + z * to[1];
		z_index = z * (CHUNK_RESOLUTION + 1);
		for (x = 0; x <= CHUNK_RESOLUTION; x++)
		{
			x_pos = from[0] + x * to[0];

			vertices[(x + z_index) * 3 + 0] = x_pos;
			vertices[(x + z_index) * 3 + 1] = -1;
			vertices[(x + z_index) * 3 + 2] = z_pos;
		}
	}

	for (z = 0; z < CHUNK_RESOLUTION; z++)
	{
		z_index = z * (CHUNK_RESOLUTION + 1);
		for (x = 0; x <= CHUNK_RESOLUTION; x++)
		{
			indices[idx++] = x + z_index;
			indices[idx++] = x + z_index + (CHUNK_RESOLUTION + 1);
		}
	}

	return Chunk_new(vertices, CHUNK_VERTICES_SIZE, indices, CHUNK_INDICES_SIZE, CHUNK_INDICES_COUNT);
}
