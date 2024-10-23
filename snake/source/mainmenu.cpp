#include "mainheader.h"

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

int savedata(std::vector < std::pair<int, std::string>>& highscores)
{
	std::vector<std::string> savevector;
	savevector.push_back(versiontag);
	
	savevector.push_back(std::to_string(highscores.size()));

	for (int i = 0; i < highscores.size(); i++)
	{
		savevector.push_back(std::to_string(highscores[i].first));
		savevector.push_back(highscores[i].second);
	}

	savetodatatxt(savevector);
	return 1;
}

int mainmenu(sf::RenderWindow& gamewindow)
{
	std::vector < std::pair<int, std::string>> highscores;
	std::vector <std::string> highscorenames;
	{
		std::vector<std::string> loadeddata = loadfromdatatxt();

		if (loadeddata[0] == "ERROR")
		{

		}
		else {
			for (int i = 2; i <= stoi(loadeddata[1])*2; i = i + 2) //loades highscores
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
	}


	gamewindow.create(sf::VideoMode(800, 600), "Snake " + versiontag, sf::Style::Close | sf::Style::Titlebar);
	{
		sf::Image icon;
		icon.loadFromFile("rsc/icon.png");
		gamewindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	bool quitfull = false;
	int returncode = 0;

	int highscore = -1;
	if (highscores.size() > 0)
	{
		highscore = highscores[0].first;
	}
	

	sf::Font font;
	font.loadFromFile("rsc/coolvetica rg.otf");

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font, 40);
	titletext.setPosition(10, 0);

	sf::Text highscoretext("Current highscore: None", font, 30);
	if (highscore != -1)
	{
		highscoretext.setString("Current highscore: " + std::to_string(highscore));
	}
	highscoretext.setPosition(0, 500);

	Button playbutton(font, "Play", { 60,200 }, { 100,50 }, 5, 25);
	playbutton.buttonedgeupdate();
	playbutton.buttontextupdate();

	Button quitbutton(font, "Quit", { 60,260 }, { 100,50 }, 5, 25);
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
				savedata(highscores);
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