#include "mainheader.h"

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

int loadhighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames)
{
	std::vector<std::string> loadeddata = loadfromtxt();

	highscores.resize(0);
	highscorenames.resize(0);

	if (loadeddata[0] == "ERROR")
	{
		return -1;
	}
	else {
		for (int i = 2; i < stoi(loadeddata[1]) * 2 + 2; i = i + 2) //loades highscores
		{
			highscores.push_back({ stoi(loadeddata[i]), loadeddata[i + 1] });
		}
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
		icon.loadFromFile("rsc/icon.png");
		gamewindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	gamewindow.setVerticalSyncEnabled(true);
}