#pragma once
#include "../Utilities/utilities.h"

class Shaders
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	//GLint colorAttribute;
	GLint iTextureLoc;
	GLint iTextCoordLoc;

	GLint WVP_Mat;

	int Init(const char* fileVertexShader, const char* fileFragmentShader);
	~Shaders();
};