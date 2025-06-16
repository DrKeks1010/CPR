#ifndef _CHUNK_H
#define _CHUNK_H

#include <glad/glad.h>
#include "linmath.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

typedef struct s_Chunk {
	GLsizei indicesCount;

	GLuint shaderId;
	mat4x4 modelMatrix;
	mat3x3 inverseMatrix;

	GLuint modelMatrixID;
	GLuint inverseMatrixID;

	VAO* vao;
	VBO* vbo;
	EBO* ebo;
} Chunk;

Chunk* Chunk_new(GLfloat* vertices, GLsizei verticesSize, GLuint* indices, GLsizei indicesSize, GLsizei indicesCount, GLuint shaderId, mat4x4 modelMatrix);
void Chunk_free(Chunk* chunk);

void Chunk_draw(Chunk* chunk);
void Chunk_recalculateModelMatrix(Chunk* chunk);

Chunk* Chunk_generate(vec2 from, vec2 to, GLuint shaderId);

#endif