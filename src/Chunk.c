#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "Chunk.h"
#include "Perlin.h"

Chunk* Chunk_new(GLfloat* vertices, GLsizei verticesSize, GLuint* indices, GLsizei indicesSize, GLsizei indicesCount, GLuint shaderId, mat4x4 modelMatrix)
{
	Chunk* chunk = calloc(1, sizeof(Chunk));
	if (chunk == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create Chunk!\n", sizeof(Chunk));
		return NULL;
	}

	chunk->indicesCount = indicesCount;
	chunk->shaderId = shaderId;
	memcpy(chunk->modelMatrix, modelMatrix, sizeof(mat4x4));
	// Todo: calculate mat3x3(inv(modelMatrix))
	
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

	VAO_linkAttrib(chunk->vao, chunk->vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(0));
	VAO_linkAttrib(chunk->vao, chunk->vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
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

#define CHUNK_RESOLUTION 32
#define CHUNK_VERTICES_SIZE (sizeof(GLfloat) * (CHUNK_RESOLUTION + 1) * (CHUNK_RESOLUTION + 1) * 6)
#define CHUNK_INDICES_COUNT ((CHUNK_RESOLUTION + 1) * CHUNK_RESOLUTION * 2 + CHUNK_RESOLUTION - 1)
#define CHUNK_INDICES_SIZE (sizeof(GLuint) * CHUNK_INDICES_COUNT)

Chunk* Chunk_generate(vec2 from, vec2 to, GLuint shaderId)
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
	GLfloat x_pos, z_pos, height;
	vec2_sub(to, from);
	vec2_mulf(to, 1.0f / CHUNK_RESOLUTION);

	vec3 dx, dz, n1, n2;

	// Vertices
	for (z = 0; z <= CHUNK_RESOLUTION; z++)
	{
		z_pos = from[1] + z * to[1];
		z_index = z * (CHUNK_RESOLUTION + 1);
		for (x = 0; x <= CHUNK_RESOLUTION; x++)
		{
			x_pos = from[0] + x * to[0];
			height = Perlin_get(x_pos, z_pos);

			vertices[(x + z_index) * 6 + 0] = x_pos;
			vertices[(x + z_index) * 6 + 1] = height;
			vertices[(x + z_index) * 6 + 2] = z_pos;

			// Calculate normal for vertex
			vec3_setXYZf(dx, -to[0], Perlin_get(x_pos - to[0], z_pos) - height, 0.0f);
			vec3_setXYZf(dz, 0.0f, Perlin_get(x_pos, z_pos - to[1]) - height, -to[1]);
			vec3_cross(n1, dz, dx);

			vec3_setXYZf(dx, to[0], Perlin_get(x_pos + to[0], z_pos) - height, 0.0f);
			vec3_setXYZf(dz, 0.0f, Perlin_get(x_pos, z_pos + to[1]) - height, to[1]);
			vec3_cross(n2, dz, dx);

			vec3_add(n1, n2);
			vec3_mulf(n1, 0.5f);
			vertices[(x + z_index) * 6 + 3] = n1[0];
			vertices[(x + z_index) * 6 + 4] = n1[1];
			vertices[(x + z_index) * 6 + 5] = n1[2];
		}
	}

	// Triangle indexing
	for (z = 0; z < CHUNK_RESOLUTION; z++)
	{
		z_index = z * (CHUNK_RESOLUTION + 1);
		for (x = 0; x <= CHUNK_RESOLUTION; x++)
		{
			indices[idx++] = x + z_index;
			indices[idx++] = x + z_index + (CHUNK_RESOLUTION + 1);
		}
		if (z < CHUNK_RESOLUTION)
			indices[idx++] = (GLuint)-1;
	}

	return Chunk_new(vertices, CHUNK_VERTICES_SIZE, indices, CHUNK_INDICES_SIZE, CHUNK_INDICES_COUNT, shaderId, mat4x4_new());
}
