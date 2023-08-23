#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include <memory>

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
	Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader);
	~Object();

	void Draw();
	void CleanUp();
	void Update(float deltaTime);
	void Move(float deltaTime);

	void SetCamera(std::shared_ptr<Camera> camera);
	void SetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position);
	
	std::shared_ptr<Camera> m_Camera;

public:
	std::shared_ptr<Model> m_model;
	std::shared_ptr<Shaders> m_shader;
	std::shared_ptr<Texture> m_texture;

	Matrix worldMatrix;
	Matrix WVP;
	float moveSpeed = 1.f;
};