#pragma once
//#include<string>
class Model
{
public:
	Model(const char* path);
	~Model();
	bool readFile(const char* path);
private:
	const char* pathToModel;
	int iFaces;
	int iVerticies;

	void processLine(const std::string& line);
};
