#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class Object
{
public:
	Object();
	~Object();

	bool Load(char* modelPath, char* texturePath);
	void Draw();

public: 
	Model* m_model;
	Texture* m_texture;
	Shaders* m_shader;


};