#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SHADER_TYPE_VERTEX 'V'
#define SHADER_TYPE_FRAGMENT 'F'
#define SHADER_TYPE_PROGRAM 'P'

static char* read_file(const char* filename)
{
	char* buffer;
	size_t length, read_length;

	FILE* fil = fopen(filename, "rb");
	if (fil == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't open File %s!\n", filename);
		return NULL;
	}

	fseek(fil, 0, SEEK_END);
	length = ftell(fil);
	if (length == 0) 
	{
		perror(NULL);
		fprintf(stderr, "File %s has length 0!\n", filename);
		fclose(fil);
		return NULL;
	}
	fseek(fil, 0, SEEK_SET);

	buffer = malloc(sizeof(char)*  (length + 1));
	if (buffer == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes whilst reading %s!\n", sizeof(char) * (length + 1), filename);
		fclose(fil);
		return NULL;
	}

	read_length = fread(buffer, sizeof(char), length, fil);
	if (read_length != length)
	{
		perror(NULL);
		fprintf(stderr, "Didn't read all bytes of File %s (%llu/%llu)!\n", filename, read_length, length);
		free(buffer);
		fclose(fil);
		return NULL;
	}

	buffer[length] = '\0';
	return buffer;
}
static GLint Shader_CompileErrors(Shader* sha, GLuint shaderID, char type)
{
	GLint hasCompiled;
	GLchar infoLog[1024];

	if (type != SHADER_TYPE_PROGRAM)
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			fprintf(stderr, "Compilation of Shader failed with error message:\n%s", infoLog);
		}
		return hasCompiled;
	}
	else
	{
		glGetProgramiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			fprintf(stderr, "Linking of Program failed with error message:\n%s", infoLog);
		}
		return hasCompiled;
	}
}

Shader* Shader_new(const char* vertexFile, const char* fragmentFile)
{
	Shader* sha = malloc(sizeof(Shader));
	if (sha == NULL)
	{
		perror(NULL);
		fprintf(stderr, "Couldn't allocate %llu bytes to create Shader object!\n", sizeof(Shader));
		return NULL;
	}

	char* vertexCode = read_file(vertexFile);
	if (vertexCode == NULL)
	{
		fprintf(stderr, "An error ocurred whilst reading Vertex Shader File %s!\n", vertexFile);
		free(sha);
		return NULL;
	}
	char* fragmentCode = read_file(fragmentFile);
	if (vertexCode == NULL || fragmentCode == NULL)
	{
		fprintf(stderr, "An error ocurred whilst reading Fragment Shader File %s!\n", fragmentFile);
		free(vertexCode);
		free(sha);
		return NULL;
	}

	// Compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vertexCode, NULL);
	glCompileShader(vertexShader);
	if (!Shader_CompileErrors(sha, vertexShader, SHADER_TYPE_VERTEX))
	{
		fprintf(stderr, "An error ocurred whilst compiling Vertex Shader File %s!\n", vertexFile);
		free(fragmentCode);
		free(vertexCode);
		free(sha);
		return NULL;
	}

	// Compile fragment Shader
	GLubyte fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**) &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	if (!Shader_CompileErrors(sha, fragmentShader, SHADER_TYPE_FRAGMENT))
	{
		fprintf(stderr, "An error ocurred whilst compiling Fragment Shader File %s!\n", fragmentFile);
		free(fragmentCode);
		free(vertexCode);
		free(sha);
		return NULL;
	}

	// Create Shader Program
	sha->ID = glCreateProgram();
	glAttachShader(sha->ID, vertexShader);
	glAttachShader(sha->ID, fragmentShader);
	glLinkProgram(sha->ID);
	if (!Shader_CompileErrors(sha, sha->ID, SHADER_TYPE_PROGRAM))
	{
		fprintf(stderr, "An error ocurred whilst linking Shader Program of Files [%s,%s]!\n", vertexFile, fragmentFile);
		free(fragmentCode);
		free(vertexCode);
		glDeleteProgram(sha->ID);
		free(sha);
		return NULL;
	}

	// Delete shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(fragmentCode);
	free(vertexCode);

	return sha;
}
inline void Shader_free(Shader* sha)
{
	glDeleteProgram(sha->ID);
	free(sha);
}

inline void Shader_Activate(Shader* sha)
{
	glUseProgram(sha->ID);
}
