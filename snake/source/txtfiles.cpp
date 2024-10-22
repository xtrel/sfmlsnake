#include "mainheader.h"

#include <fstream>

#include <cassert>
#include <cstdlib>
#include <filesystem>

/*
CURRENT FORMAT OF data.txt

0 - Version tag
1 - number of highscores
2 - highscore
2+1 - name
4 - highscore
4+1 -name
...
NoH - highscore
NoH + 1 - name

*/

std::vector<std::string> loadfromdatatxt()
{
	std::ifstream fin;
	fin.open("gamedata/data.txt");

	if (!fin.is_open())
	{
		return {"ERROR"};
	}

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

	if (!fout.is_open())
	{
		std::filesystem::create_directory("gamedata");
		fout.close();
		fout.open("gamedata/data.txt");
	}

	if (!fout.is_open())
	{
		return -1;
		fout.close();
	}

	for (int i = 0; i < datavector.size(); i++)
	{
		fout << datavector[i] << "\n";
	}

	fout.close();

	return 1;
}

bool writetolog(std::string text, std::string path)
{
	std::ifstream fin;
	fin.open("gamedata/" + path);

	std::vector<std::string> file;
	std::string tempstring;

	while (fin >> tempstring)
	{
		file.push_back(tempstring);
	}

	fin.close();

	file.push_back(text);

	std::ofstream fout;
	fout.open("gamedata/" + path);

	if (!fout.is_open())
	{
		std::filesystem::create_directory("gamedata");
		fout.close();
		fout.open("gamedata/" + path);
	}

	if (!fout.is_open())
	{
		return -1;
		fout.close();
	}


	for (int i = 0; i < file.size(); i++)
	{
		fout << file[i] << "\n";
	}

	fout.close();

	return 1;
}