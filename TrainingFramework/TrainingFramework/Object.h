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
	Object(char* modelPath, char* texturePath, char* VSpath, char* FSpath);
	Object(Model* model, Texture* texture, Shaders* shader);
	~Object();

	//bool Load(char* modelPath, char* texturePath, char* VSpath, char* FSpath);

	void Draw();
	void CleanUp();
	void Update(float deltaTime);
	void Move(float deltaTime);

	void SetCamera(Camera* camera);
	void SetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position);
	Camera* m_Camera;

public:
	Model* m_model;
	Texture* m_texture;
	Shaders* m_shader;

	Matrix worldMatrix;
	Matrix WVP;
	float moveSpeed = 1.f;


};