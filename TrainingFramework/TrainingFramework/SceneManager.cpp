#include "stdafx.h"
#include "SceneManager.h"
#include "ResourcesManager.h"
#include  "Globals.h"

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

bool SceneManager::Init(char* pathToSM)
{
	std::ifstream file(pathToSM);
	if (!file.is_open()) {
		printf("Cannot open SceneManager.txt\n");
		return false;
	}

	std::string line;
	std::getline(file, line);
	int NumOfObject;

	//read object property
	sscanf_s(line.c_str(), "#Objects: %d", &NumOfObject);
	m_Objects = new std::vector<Object*>();
	for (int i = 0; i < NumOfObject; i++) {
		int Model_ID;
		std::getline(file, line);
		std::getline(file, line);
		sscanf_s(line.c_str(), "MODEL %d", &Model_ID);

		std::shared_ptr<Model> model = ResourcesManager::GetInstance()->getModel(Model_ID);
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Shaders> shader;

		int NumofTextures;
		std::getline(file, line);
		sscanf_s(line.c_str(), "TEXTURES %d", &NumofTextures);
		for (int j = 0; j < NumofTextures; j++) {
			std::getline(file, line);
			int TextureID;
			sscanf_s(line.c_str(), "TEXTURE %d", &TextureID);
			texture = ResourcesManager::GetInstance()->getTexture(TextureID);
		}
		int shader_ID;
		std::getline(file, line);
		sscanf_s(line.c_str(), "SHADER %d", &shader_ID);
		shader = ResourcesManager::GetInstance()->getShader(shader_ID);

		Object* object = new Object(model, texture, shader);
		Vector3 scalation, rotation, position;
		float a, b, c;
		std::getline(file, line);
		sscanf_s(line.c_str(), "%*s %f, %f, %f", &a, &b, &c);
		position = Vector3(a, b, c);
		std::getline(file, line);
		sscanf_s(line.c_str(), "%*s %f, %f, %f", &a, &b, &c);
		rotation = Vector3(a, b, c);
		std::getline(file, line);
		sscanf_s(line.c_str(), "%*s %f, %f, %f", &a, &b, &c);
		scalation = Vector3(a, b, c);
		position.Display();
		rotation.Display();
		scalation.Display();
		object->SetModelMatrix(scalation, rotation, position);
		m_Objects->push_back(object);

		model = nullptr;
		texture = nullptr;
		shader = nullptr;
		object = nullptr;

	}
	std::getline(file, line);
	float Near, Far, Fov, speed;
	std::getline(file, line);
	sscanf_s(line.c_str(), "%*s %f", &Near);
	std::getline(file, line);
	sscanf_s(line.c_str(), "%*s %f", &Far);
	std::getline(file, line);
	sscanf_s(line.c_str(), "%*s %f", &Fov);
	std::getline(file, line);
	sscanf_s(line.c_str(), "%*s %f", &speed);
	m_Camera = std::make_shared<Camera>(Near, Far, Fov);
	m_Camera->m_MoveSpeed = speed;

	for (auto s : *m_Objects) {
		s->SetCamera(m_Camera);
	}

	return true;
}
void SceneManager::Draw()
{
	for (auto c : *m_Objects) {
		c->Draw();
	}
	//m_Objects->at(1)->Draw();

}
void SceneManager::Update(float deltaTime)
{
	for (auto s : *m_Objects) {
		s->Update(deltaTime);
	}
	if (KeyPress & 1) {
		//obj->Move(deltaTime);
		m_Camera->Move(Camera_Movement::LEFT, deltaTime);
	}
	if (KeyPress & (1 << 1)) {
		m_Camera->Move(RIGHT, deltaTime);
	}
	if (KeyPress & (1 << 2)) {
		m_Camera->Move(FORWARD, deltaTime);
	}
	if (KeyPress & (1 << 3)) {
		m_Camera->Move(BACKWARD, deltaTime);
	}
	if (KeyPress & (1 << 4)) {
		m_Camera->RotateCounterClockWise(Camera_Rotate::yAxis, deltaTime);
	}
	if (KeyPress & (1 << 5)) {
		m_Camera->RotateClockWise(yAxis, deltaTime);
	}
	if (KeyPress & (1 << 6)) {
		m_Camera->RotateCounterClockWise(xAxis, deltaTime);
	}
	if (KeyPress & (1 << 7)) {
		m_Camera->RotateClockWise(xAxis, deltaTime);
	}
}
void SceneManager::Key(unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		KeyPress = 0;
		switch (key)
		{
		case KEY_LEFT:
			KeyPress |= 1;
			break;
		case KEY_RIGHT:
			KeyPress |= 1 << 1;
			break;
		case KEY_UP:
			KeyPress |= 1 << 2;
			break;
		case KEY_DOWN:
			KeyPress |= 1 << 3;
			break;
		case KEY_MOVE_LEFT:
			KeyPress |= 1 << 4;
			break;
		case KEY_MOVE_RIGHT:
			KeyPress |= 1 << 5;
			break;
		case KEY_MOVE_FORWARD:
			KeyPress |= 1 << 6;
			break;
		case KEY_MOVE_BACKWORD:
			KeyPress |= 1 << 7;
			break;
		default:
			break;
		}

	}
	else {
		switch (key)
		{
		case KEY_LEFT:
			KeyPress ^= 1;
			break;
		case KEY_RIGHT:
			KeyPress ^= 1 << 1;
			break;
		case KEY_UP:
			KeyPress ^= 1 << 2;
			break;
		case KEY_DOWN:
			KeyPress ^= 1 << 3;
			break;
		case KEY_MOVE_LEFT:
			KeyPress ^= 1 << 4;
			break;
		case KEY_MOVE_RIGHT:
			KeyPress ^= 1 << 5;
			break;
		case KEY_MOVE_FORWARD:
			KeyPress ^= 1 << 6;
			break;
		case KEY_MOVE_BACKWORD:
			KeyPress ^= 1 << 7;
			break;
		default:
			break;
		}
	}
}

SceneManager* SceneManager::s_Instance = nullptr;

void SceneManager::CleanUp()
{
	for (auto& s : *m_Objects) {
		s->CleanUp();
		delete s;
	}
	m_Objects->clear();
	delete m_Objects;
	if (s_Instance)
	{
		delete s_Instance;
	}
	//s_Instance = nullptr;

}