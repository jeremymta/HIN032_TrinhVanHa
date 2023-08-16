#include "stdafx.h"
#include <fstream>
#include "ResourcesManager.h"

void LoadModel(GLint count, std::ifstream& filePtr);
void LoadShader(GLint count, std::ifstream& filePtr);
void LoadTexture(GLint count, std::ifstream& filePtr);


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
	std::string path = "../Resources/Scenes/" + filename;
	std::ifstream resourcesFile(path);
	std::string typeBuff;
	GLint count, type;
	bool valid = true;
	while (!resourcesFile.eof() && valid)
	{
		resourcesFile >> typeBuff;
		type = ParseType(typeBuff);
		switch (type)
		{
		case TYPE_MODEL:
			resourcesFile >> count;
			LoadModel(count, resourcesFile);
			break;
		case TYPE_SHADER:
			resourcesFile >> count;
			break;
		case TYPE_TEXTURE:
			resourcesFile >> count;
			break;
		case TYPE_INVALID:
			std::cout << "Invalid resources file, abort loading resources\n";
			valid = false;
			break;
		default:
			break;
		}
	}

	resourcesFile.close();
}

std::shared_ptr<Model> ResourcesManager::getModel(GLint id)
{
	return std::shared_ptr<Model>();
}

std::shared_ptr<Shaders> ResourcesManager::getShader(GLint id)
{
	return std::shared_ptr<Shaders>();
}

std::shared_ptr<Texture> ResourcesManager::getTexture(GLint id)
{
	return std::shared_ptr<Texture>();
}


GLint ParseType(const std::string& type)
{
	if (type == "#Models:")
		return TYPE_MODEL;
	if (type == "#Shaders:")
		return TYPE_SHADER;
	if (type == "#Textures:")
		return TYPE_TEXTURE;
	return TYPE_INVALID;
}

void LoadModel(GLint count, std::ifstream& filePtr)
{

}

void LoadShader(GLint count, std::ifstream& filePtr)
{

}

void LoadTexture(GLint count, std::ifstream& filePtr)
{

}