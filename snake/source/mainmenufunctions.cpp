#include "mainheader.h"
#include "tinyfiledialogs.h"

int updatehighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames, int currentscore, std::string namefromround)
{
	std::string tempstring = namefromround + ";" + versiontag;
	highscores.push_back({ currentscore,tempstring });

	for (int i = highscores.size() - 1; i > 0; i--)
	{
		if (highscores[i].first > highscores[i - 1].first)
		{
			std::pair<int, std::string> temp = highscores[i - 1];
			highscores[i - 1] = highscores[i];
			highscores[i] = temp;
		}
	}

	highscorenames.resize(0);
	for (int i = 0; i < highscores.size(); i++) //Could be more efficient
	{
		size_t pos = highscores[i].second.find(';');
		if (pos == std::string::npos)
		{
			highscorenames.push_back(highscores[i].second);
			highscores[i].second = highscores[i].second + ";before V1.2.1.1";
		}
		else {
			highscorenames.push_back(highscores[i].second.substr(0, pos));
		}
	}

	return 1;
}

int centertext(sf::Text& text, bool centerhor, bool centerver)
{
	sf::FloatRect textrect = text.getLocalBounds();
	int h = textrect.height;
	int w = textrect.width;
	if (centerhor)
	{
		text.setOrigin(textrect.left + textrect.width / 2.0f, 0);
	}
	if (centerver)
	{
		text.setOrigin(0, textrect.top + textrect.height / 2.0f);
	}
	if (centerver && centerhor)
	{
		text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
	}
	return 1;
}

int TORELXPOS(double pos, int srw)
{
	pos = pos / 800.f;
	pos = pos * srw;
	return round(pos);
}

int TORELYPOS(double pos, int srh)
{
	pos = pos / 600.f;
	pos = pos * srh;
	return round(pos);
}

int savehighscoredata(std::vector < std::pair<int, std::string>>& highscores)
{
	std::vector<std::string> savevector;
	savevector.push_back(versiontag);

	savevector.push_back(std::to_string(highscores.size()));

	for (int i = 0; i < highscores.size(); i++)
	{
		savevector.push_back(std::to_string(highscores[i].first));
		savevector.push_back(highscores[i].second);
	}

	savetotxt(savevector);
	return 1;
}

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

int loadhighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames)
{
	std::vector<std::string> loadeddata = loadfromtxt();

	if (loadeddata.size() == 0 || loadeddata[0] == "ERROR")
	{
		return 0;
	}

	highscores.resize(0);
	highscorenames.resize(0);

	if (!is_int(loadeddata[1]))
	{
		if (errorboxyesno("Corrupted data.txt file.", "The amount of highscores contains letters, which it should not. Attempt fix?") == 1)
		{
			for (int i = 0; i < loadeddata[1].length(); i++)
			{
				if (!std::isdigit(loadeddata[1][i]))
				{
					loadeddata[1].erase(i,1);
					i = -1;
				}
			}

			if (!is_int(loadeddata[1]))
			{
				if (errorboxyesno("Corrupted data.txt file.", "Fix failed. Delete file? (Press no to leave)") == 1)
				{
					return 0;
				}
				else {
					return -1;
				}
			}
			else {
				
			}
		}
		else {
			return -1;
		}
	}

	if (stoi(loadeddata[1]) * 2 + 2 != loadeddata.size())
	{
		if (errorboxyesno("Corrupted data.txt file.", "Mismatch between saved highscores and their saved amount. Attempt fix?") == 1)
		{
			loadeddata[1] = std::to_string((loadeddata.size() - 2)/2);

			if (stoi(loadeddata[1]) * 2 + 2 != loadeddata.size())
			{
				if (errorboxyesno("Corrupted data.txt file.", "Fix failed. Delete file? (Press no to leave)") == 1)
				{
					return 0;
				}
				else {
					return -1;
				}
			}
			else {
				
			}
		}
		else {
			return -1;
		}
	}

	for (int i = 2; i < stoi(loadeddata[1]) * 2 + 2; i = i + 2) //loades highscores
	{
		if (!is_int(loadeddata[i]))
		{
			for (int k = 0; k < loadeddata[i].length(); k++)
			{
				if (!std::isdigit(loadeddata[i][k]))
				{
					loadeddata[i].erase(k, 1);
					k = -1;
				}
			}
			if (!is_int(loadeddata[i]))
			{
				if (errorboxyesno("Corrupted data.txt file.", "Highscore in line " + std::to_string(i) + ":\n" + loadeddata[i] + "\n" + loadeddata[i + 1] + "\nIs corrupted. Do you want to delete it?") == 1)
				{
					loadeddata.erase(loadeddata.begin() + i);
					loadeddata.erase(loadeddata.begin() + i);
					loadeddata[1] = std::to_string(stoi(loadeddata[1])-1);
					i = 2;
				}
				else {
					return -1;
				}
			}
		}
		if (countacharinastring(loadeddata[i + 1], ';') != 1)
		{
			if (countacharinastring(loadeddata[i + 1], ';') == 0)
			{
				loadeddata[i + 1] = loadeddata[i + 1] + ";" + loadeddata[i + 1] + "_FXD_" + versiontag;
			}
			if (countacharinastring(loadeddata[i + 1], ';') != 1)
			{
				if (errorboxyesno("Corrupted data.txt file.", "Highscore in line " + std::to_string(i) + ":\n" + loadeddata[i] + "\n" + loadeddata[i + 1] + "\nIs corrupted. Do you want to delete it?") == 1)
				{
					loadeddata.erase(loadeddata.begin() + i);
					loadeddata.erase(loadeddata.begin() + i);
					loadeddata[1] = std::to_string(stoi(loadeddata[1]) - 1);
					i = 2;
				}
				else {
					return -1;
				}
			}
			else {

			}
		}
	}

	for (int i = 2; i < stoi(loadeddata[1]) * 2 + 2; i = i + 2) //loades highscores
	{
		highscores.push_back({ stoi(loadeddata[i]), loadeddata[i + 1] });
	}

	for (int i = 0; i < highscores.size(); i++)
	{
		size_t pos = highscores[i].second.find(';');
		if (pos == std::string::npos)
		{
			highscorenames.push_back(highscores[i].second);
			highscores[i].second = highscores[i].second + ";before V1.2.1.1";
		}
		else {
			highscorenames.push_back(highscores[i].second.substr(0, pos));
		}
	}
	return 1;
}

int createwindow(sf::RenderWindow& gamewindow)
{
	if (gamewindow.isOpen())
	{
		gamewindow.close();
	}
	int fullscreenflag = 0;
	if (fullscreen)
	{
		fullscreenflag = 8;
	}
	gamewindow.create(sf::VideoMode(screenreswidth, screenresheight), "Snake " + versiontag, sf::Style::Close | sf::Style::Titlebar | fullscreenflag);
	{
		sf::Image icon;
		if (!icon.loadFromFile("rsc/icon.png"))
		{

			errorbox("Could not load icon image.", "Could not load icon.png in rsc folder. Try reinstalling your game or putting the file back.");
			return -1;
		}
		gamewindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	gamewindow.setVerticalSyncEnabled(true);
	if (!gamewindow.isOpen())
	{
		errorbox("Error during window creation.", "");
		return -1;
	}
	return 1;
}

void errorbox(std::string title, std::string message)
{
	tinyfd_messageBox(title.c_str(), message.c_str(), "ok", "error", 1);
	return;
}

int errorboxyesno(std::string title, std::string message)
{
	int retmes = tinyfd_messageBox(title.c_str(), message.c_str(), "yesno", "error", 1);
	return retmes;
}

bool is_int(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int countacharinastring(std::string string, char lookchar)
{
	int count = 0;

	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == lookchar) count++;
	}

	return count;
}