#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

enum Movement {
	MOVE_LEFT,
	MOVE_RIGHT,
	UP,
	DOWN
};

enum Rotation {
	ROT_LEFT, ROT_RIGHT
};

class Object
{
public:
	Object();
	~Object();

	bool Load(char* modelPath, char* texturePath, char* VSpath, char* FSpath);
	
	void Draw();

	void CleanUp();

	void Update(float deltaTime);

	void Move(float deltaTime);

public: 
	Model* m_model;
	Texture* m_texture;
	Shaders* m_shader;
	Camera* camera;

	Matrix model;
	Matrix WVP;
	float moveSpeed = 1.f;


};