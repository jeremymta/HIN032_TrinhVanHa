﻿#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include "Singleton.h"
#include "Model.h"
#include "Shaders.h"
#include "Texture.h"
#include "Camera.h"
#include "Globals.h"

enum ResourceType
{
	RT_MODEL,
	RT_SHADER,
	RT_TEXTURE,
	RT_INVALID = -1
};

class ResourcesManager : public SingletonDclp<ResourcesManager>
{
public:
	// APIs
	void Init();
	void CleanUp();
	void LoadResources(const std::string& filename);
	std::shared_ptr<Model> getModel(GLint id);
	std::shared_ptr<Shaders> getShader(GLint id);
	std::shared_ptr<Texture> getTexture(GLint id);

	bool m_init;
private:
	std::unordered_map<GLint, std::shared_ptr<Model>> m_modelList;
	std::unordered_map<GLint, std::shared_ptr<Shaders>> m_shaderList;
	std::unordered_map<GLint, std::shared_ptr<Texture>> m_textureList;

	// Utilities
	void LoadModel(GLint count, std::ifstream& filePtr);
	void LoadShader(GLint count, std::ifstream& filePtr);
	void LoadTexture(GLint count, std::ifstream& filePtr);
};