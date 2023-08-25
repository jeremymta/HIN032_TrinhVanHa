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

	void SetRotation(Vector3 rotation);
	void SetScale(Vector3 scale);
	void SetPos(Vector3 pos);
	void AttachCamera(std::shared_ptr<Camera> camera);
	void Set2DSize(int x, int y);
	bool m_changed;

public:

	Vector3 m_pos;
	Vector3 m_scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 m_rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_translation = Vector3(0.0f, m_pos.y, 0.0f);

	std::shared_ptr<Model> m_model;
	std::shared_ptr<Shaders> m_shader;
	std::shared_ptr<Texture> m_texture;

	Matrix worldMatrix;
	Matrix WVP;
	float moveSpeed = 1.f;

};