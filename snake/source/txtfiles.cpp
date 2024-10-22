#include "mainheader.h"

#include <fstream>

std::vector<std::string> loadfromdatatxt()
{
	std::ifstream fin;
	fin.open("gamedata/data.txt");

	std::vector<std::string> retvector;
	std::string tempstring;

	while (fin >> tempstring)
	{
		retvector.push_back(tempstring);
	}

	fin.close();

	return retvector;
}

int savetodatatxt(std::vector<std::string> datavector)
{
	std::ofstream fout;
	fout.open("gamedata/data.txt");

	for (int i = 0; i < datavector.size(); i++)
	{
		fout << datavector[i] << "\n";
	}

	fout.close();

	return 1;
}

bool writetolog(std::string text)
{
	std::ifstream fin;
	fin.open("gamedata/log.txt");

	std::vector<std::string> file;
	std::string tempstring;

	while (fin >> tempstring)
	{
		file.push_back(tempstring);
	}

	fin.close();

	file.push_back(text);

	std::ofstream fout;
	fout.open("gamedata/log.txt");

	for (int i = 0; i < file.size(); i++)
	{
		fout << file[i] << "\n";
	}

	fout.close();

	return 1;
}