#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(const char* fileVertexShader, const char* fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	//colorAttribute = glGetAttribLocation(program, "a_color");

	//setting texture uniform:
	//1. Lay vi tri uniform texture
	iTextureLoc = glGetUniformLocation(program, "u_texture");
	iTextCoordLoc = glGetAttribLocation(program, "a_uv");

	// Ma tran WVP
	WVP_Mat = glGetUniformLocation(program, "u_WVP");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}