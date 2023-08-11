#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

class Object
{
public:
	Object();
	~Object();

	bool Load(char* modelPath, char* texturePath, char* VSpath, char* FSpath);
	
	void Draw();

	void CleanUp();

public: 
	Model* m_model;
	Texture* m_texture;
	Shaders* m_shader;
	Camera* camera;


};