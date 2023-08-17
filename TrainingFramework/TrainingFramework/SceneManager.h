#pragma once
#include <unordered_map>
#include "Singleton.h"
#include "Camera.h"
#include "Object.h"

enum ElementType
{
	ET_CAMERA,
	ET_OBJECT,
	ET_INVALID = -1
};

class SceneManager final : public SingletonDclp<SceneManager>
{
public:
	// APIs
	void Init();
	void CleanUp();
	void LoadElements(const std::string& filename);
	std::shared_ptr<Camera> getCamera(GLint camera_id);
	std::shared_ptr<Object> getObject(GLint object_id);

	bool m_init;

private:
	std::unordered_map<GLint, std::shared_ptr<Camera>> m_cameraList;
	std::unordered_map<GLint, std::shared_ptr<Object>> m_objectList;

	// Utilities
	void LoadObject(int count, std::ifstream& file);
	void LoadCamera(int count, std::ifstream& file);
};