#pragma once

class Globals
{
public:
	static const int screenWidth = 960;
	static const int screenHeight = 720;
	inline static const std::string modelPath = "../Resources/Models/";
	inline static const std::string shaderPath = "../Resources/Shaders/";
	inline static const std::string texturePath = "../Resources/Textures/";
	inline static const std::string scenePath = "../Resources/Scenes/";
};

#define KEY_LEFT			VK_LEFT
#define KEY_RIGHT			VK_RIGHT
#define KEY_UP				VK_UP
#define KEY_DOWN			VK_DOWN
#define KEY_MOVE_LEFT		'A'
#define KEY_MOVE_RIGHT		'D'
#define KEY_MOVE_FORWARD	'W'
#define KEY_MOVE_BACKWORD	'S'
