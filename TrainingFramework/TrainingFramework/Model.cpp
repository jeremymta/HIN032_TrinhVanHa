#include "stdafx.h"
#include "Model.h"
#include <fstream>
#include <iostream>

Model::Model(const char* path)
{

}

bool Model::readFile(const char* path)
{
	std::ifstream file(path);
	if (file.is_open()) {
		std::cerr << "Error while opening file" << std::endl;
		return false;
	}

	return false;
}

void Model::processLine(const std::string& line)
{
}
