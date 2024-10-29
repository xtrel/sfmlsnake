#include "mainheader.h"

int screenreswidth = 800;
int screenresheight = 600;
bool fullscreen = false;

int TORELXPOS(double pos)
{
	pos = pos / 800.f;
	pos = pos * screenreswidth;
	return round(pos);
}

int TORELSIZE(double pos)
{
	double pos1 = pos / 800.f;
	pos1 = pos1 * screenreswidth;

	double pos2 = pos / 600.f;
	pos2 = pos2 * screenresheight;

	return round((pos1+pos2)/2.f);
}

int TORELYPOS(double pos)
{
	pos = pos / 600.f;
	pos = pos * screenresheight;
	return round(pos);
}

int updatehighscores(std::vector < std::pair<int, std::string>>& highscores, int currentscore, int& highscore)
{
	std::string tempstring = "placeholder;"+versiontag;
	highscores.push_back({ currentscore,tempstring});

	for (int i = highscores.size() - 1; i > 0; i--)
	{
		if (highscores[i].first > highscores[i - 1].first)
		{
			std::pair<int, std::string> temp = highscores[i - 1];
			highscores[i - 1] = highscores[i];
			highscores[i] = temp;
		}
	}

	if (highscores.size() > 10)
	{
		highscores.resize(10);
	}

	highscore = highscores[0].first;
	return 1;
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
	if (loadeddata[0] == "ERROR")
	{
		return -1;
	}
	else {
		for (int i = 2; i <= stoi(loadeddata[1]) * 2; i = i + 2) //loades highscores
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

int mainmenu(sf::RenderWindow& gamewindow)
{
	std::vector < std::pair<int, std::string>> highscores;
	std::vector <std::string> highscorenames;
	{
		std::vector<std::string> loadeddata = loadfromtxt();

		{ //data.txt
			loadhighscores(highscores, highscorenames);
		}

		loadeddata.resize(0);

		{ //set.txt
			loadeddata = loadfromtxt("set.txt");
			if (loadeddata[0] == "ERROR")
			{
				savetotxt({ "800","600","0" }, "set.txt");
			}
			else {
				screenreswidth = std::stoi(loadeddata[0]);
				screenresheight = std::stoi(loadeddata[1]);
				fullscreen = std::stoi(loadeddata[2]);
			}
		}
	}

	{
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
	}

	bool quitfull = false;
	int returncode = 0;

	int highscore = -1;
	if (highscores.size() > 0)
	{
		highscore = highscores[0].first;
	}
	
	sf::Font font;
	font.loadFromFile("rsc/munro.ttf");

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font, TORELSIZE(40));
	titletext.setPosition(TORELXPOS(10), TORELYPOS(10));

	sf::Text highscoretext("Current highscore: None", font, TORELSIZE(30));
	if (highscore != -1)
	{
		highscoretext.setString("Current highscore: " + std::to_string(highscore));
	}
	highscoretext.setPosition(TORELXPOS(10), TORELYPOS(560));

	Button playbutton(font, "Play", { TORELXPOS(60),TORELYPOS(200) }, { TORELXPOS(100),TORELYPOS(50) }, TORELSIZE(5), TORELSIZE(25));
	playbutton.buttonedgeupdate();
	playbutton.buttontextupdate();

	Button quitbutton(font, "Quit", { TORELXPOS(60),TORELYPOS(260) }, { TORELXPOS(100),TORELYPOS(50) }, TORELSIZE(5), TORELSIZE(25));
	quitbutton.buttonedgeupdate();
	quitbutton.buttontextupdate();

	while (!quitfull)
	{
		int gameloopreturncode = -69;
		sf::Event windowevent;
		
		while (gamewindow.pollEvent(windowevent))
		{
			bool startgame = false;
			bool quit = false;
			if (windowevent.type == sf::Event::Closed)
			{
				quit = true;
			}
			if (windowevent.type == sf::Event::MouseButtonReleased)
			{
				if (playbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					startgame = true;
				}
				else if (quitbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					quit = true;
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter || windowevent.key.code == sf::Keyboard::Space)
				{
					startgame = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Q)
				{
					quit = true;
				}
			}
			if (startgame)
			{
				int scorefromround = -1;
				gameloopreturncode = screenloopandinit(gamewindow, scorefromround);
				updatehighscores(highscores, scorefromround,highscore);
				highscoretext.setString("Current highscore: " + std::to_string(highscore));
				savehighscoredata(highscores);
				loadhighscores(highscores, highscorenames);
				if (gameloopreturncode == 0)
				{
					quit = true;
				}
			}

			if (quit)
			{
				gamewindow.close();
				returncode = 1;
				quitfull = true;
			}
		}

		gamewindow.clear();
		gamewindow.draw(titletext);
		gamewindow.draw(highscoretext);
		gamewindow.draw(playbutton);
		gamewindow.draw(quitbutton);
		gamewindow.display();
	}

	return returncode;
}