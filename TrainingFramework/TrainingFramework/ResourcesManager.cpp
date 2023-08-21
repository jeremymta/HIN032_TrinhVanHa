#include "stdafx.h"
#include <fstream>
#include <algorithm>
#include "ResourcesManager.h"
#include "Globals.h"

GLint ParseResourceType(const std::string& type);

void ResourcesManager::Init()
{
}

void ResourcesManager::CleanUp()
{
	for (auto it = m_modelList.begin(); it != m_modelList.end(); ++it)
	{
		auto ibo = it->second->getIBOid();
		auto vbo = it->second->getVBOid();
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		it->second.reset();
	}
	for (auto it = m_shaderList.begin(); it != m_shaderList.end(); ++it)
	{
		glDeleteShader(it->second->fragmentShader);
		glDeleteShader(it->second->vertexShader);
		it->second.reset();
	}
	for (auto it = m_textureList.begin(); it != m_textureList.end(); ++it)
	{
		auto texId = it->second->getTextureId();
		glDeleteTextures(1, &texId);
		it->second.reset();
	}

	m_modelList.clear();
	m_shaderList.clear();
	m_textureList.clear();

}

void ResourcesManager::LoadResources(const std::string& filename)
{
	std::string path = Globals::scenePath + filename;
	std::ifstream resourcesFile(path);
	if (!resourcesFile.is_open())
	{
		std::cerr << "Error opening file " << path << "\n";
		m_init = false;
		return;
	}
	std::string skipStr;
	GLint count, type;
	bool valid = true;
	do
	{
		if (!(resourcesFile >> skipStr >> count))
		{
			break;
		}
		type = ParseResourceType(skipStr);
		switch (type)
		{
		case RT_MODEL:
			LoadModel(count, resourcesFile);
			break;
		case RT_SHADER:
			LoadShader(count, resourcesFile);
			break;
		case RT_TEXTURE:
			LoadTexture(count, resourcesFile);
			break;
		case RT_INVALID:
			valid = false;
			break;
		default:
			break;
		}
	} while (valid);
	if (!valid) std::cout << "Resources file format error, abort loading resources\n";
	resourcesFile.close();
}

std::shared_ptr<Model> ResourcesManager::getModel(GLint id)
{
	auto it = m_modelList.find(id);
	if (it != m_modelList.end())
	{
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<Shaders> ResourcesManager::getShader(GLint id)
{
	auto it = m_shaderList.find(id);
	if (it != m_shaderList.end())
	{
		return it->second;
	}
	std::cerr << "ERR: Shader with id " << id << " not found!\n";
	return nullptr;
}

std::shared_ptr<Texture> ResourcesManager::getTexture(GLint id)
{
	auto it = m_textureList.find(id);
	if (it != m_textureList.end())
	{
		return it->second;
	}
	std::cerr << "ERR: Texture with id " << id << " not found!\n";
	return nullptr;
}


GLint ParseResourceType(const std::string& type)
{
	if (type == "#Models:")
		return RT_MODEL;
	if (type == "#Shaders:")
		return RT_SHADER;
	if (type == "#2D_Textures:")
		return RT_TEXTURE;
	if (type == "#Sounds:")
		return RT_SOUND;
	return RT_INVALID;
}

void ResourcesManager::LoadModel(GLint count, std::ifstream& filePtr)
{
	std::string skipStr, filename;
	GLint id;
	for (int i = 0; i < count; ++i)
	{
		filePtr >> skipStr >> id >> skipStr >> filename;
		filename.erase(std::remove_if(filename.begin(), filename.end(), [](char c) {return c == '\"'; }), filename.end());
		filename = Globals::modelPath + filename;
		std::shared_ptr<Model> model = std::make_shared<Model>();
		//model->LoadModel("../Resources/Models/Woman2.nfg");
		model->LoadModel(filename);
		m_modelList.insert(std::make_pair(id, model));
	}
}

void ResourcesManager::LoadShader(GLint count, std::ifstream& filePtr)
{
	std::string skipStr, vs, fs;
	GLint id;
	for (int i = 0; i < count; ++i)
	{
		filePtr >> skipStr >> id >> skipStr >> vs >> skipStr >> fs;
		vs.erase(std::remove_if(vs.begin(), vs.end(), [](char c) {return c == '\"'; }), vs.end());
		fs.erase(std::remove_if(fs.begin(), fs.end(), [](char c) {return c == '\"'; }), fs.end());
		vs = Globals::shaderPath + vs;
		fs = Globals::shaderPath + fs;
		auto shader = std::make_shared<Shaders>();
		//shader->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
		shader->Init(vs.c_str(), fs.c_str());
		m_shaderList.insert(std::make_pair(id, shader));
	}
}

void ResourcesManager::LoadTexture(GLint count, std::ifstream& filePtr)
{
	std::string skipStr, filename, wrap, filter;
	GLint id;
	for (int i = 0; i < count; ++i)
	{
		filePtr >> skipStr >> id >> skipStr >> filename >> skipStr >> wrap >> skipStr >> filter;
		filename.erase(std::remove_if(filename.begin(), filename.end(), [](char c) {return c == '\"'; }), filename.end());
		filename = Globals::texturePath + filename;
		auto texture = std::make_shared<Texture>();
		//texture->LoadTexture("../Resources/Textures/Woman2.tga");
		texture->LoadTexture(filename);
		if (wrap == "CLAMP")
		{
			texture->SetWrap(GL_CLAMP_TO_EDGE);
		}
		else if (wrap == "REPEAT")
		{
			texture->SetWrap(GL_REPEAT);
		}
		if (filter == "LINEAR")
		{
			texture->SetFilter(GL_LINEAR);
		}
		else if (filter == "NEAREST")
		{
			texture->SetFilter(GL_NEAREST);
		}
		m_textureList.insert(std::make_pair(id, texture));
	}
}

