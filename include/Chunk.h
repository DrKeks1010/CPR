#ifndef _CHUNK_H
#define _CHUNK_H

#include <glad/glad.h>
#include "vec2.h"
#include "vec3.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

typedef struct s_Chunk {
	GLsizei indicesCount;

	VAO* vao;
	VBO* vbo;
	EBO* ebo;
} Chunk;

Chunk* Chunk_new(GLfloat* vertices, GLsizei verticesSize, GLuint* indices, GLsizei indicesSize, GLsizei indicesCount);
void Chunk_free(Chunk* chunk);

void Chunk_draw(Chunk* chunk);

Chunk* Chunk_generate(vec2 from, vec2 to);

#endif