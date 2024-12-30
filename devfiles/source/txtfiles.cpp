#include "mainheader.h"

#include <fstream>

#include <cassert>
#include <cstdlib>
#include <filesystem>

std::vector<std::string> loadfromtxt(std::string filename)
{
	std::ifstream fin;
	fin.open("gamedata/"+ filename);

	if (!fin.is_open())
	{
		return {"ERROR"};
	}

	std::vector<std::string> retvector;
	std::string tempstring;

	while (std::getline(fin,tempstring))
	{
		retvector.push_back(tempstring);
	}

	fin.close();

	return retvector;
}

int savetotxt(std::vector<std::string> datavector,std::string filename)
{
	std::ofstream fout;
	fout.open("gamedata/"+ filename);

	if (!fout.is_open())
	{
		std::filesystem::create_directory("gamedata");
		fout.close();
		fout.open("gamedata/"+ filename);
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