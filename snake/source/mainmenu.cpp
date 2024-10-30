#include "mainheader.h"
#include "mainmenuheader.h"

int screenreswidth = 800;
int screenresheight = 600;
bool fullscreen = false;

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
	
	createwindow(gamewindow);

	bool quitfull = false;
	int returncode = 0;

	int highscore = -1;
	if (highscores.size() > 0)
	{
		highscore = highscores[0].first;
	}
	
	sf::Font font;
	font.loadFromFile("rsc/munro.ttf");

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font, TORELXPOS(40));
	titletext.setPosition(TORELXPOS(10), TORELYPOS(10));

	sf::Text highscoretext("Current highscore: None", font, TORELXPOS(30));
	if (highscore != -1)
	{
		highscoretext.setString("Current highscore: " + std::to_string(highscore));
	}
	highscoretext.setPosition(TORELXPOS(10), TORELYPOS(560));

	Button playbutton(font, "Play", { TORELXPOS(60),TORELYPOS(200) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	Button quitbutton(font, "Quit", { TORELXPOS(60),TORELYPOS(320) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	Button setbutton(font, "Settings", { TORELXPOS(60),TORELYPOS(260) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	while (!quitfull)
	{
		int gameloopreturncode = -69;
		sf::Event windowevent;
		
		while (gamewindow.pollEvent(windowevent))
		{
			bool startgame = false;
			bool quit = false;
			bool settings = false;
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
				else if (setbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					settings = true;
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
				loadhighscores(highscores, highscorenames);
				updatehighscores(highscores, scorefromround,highscore);
				highscoretext.setString("Current highscore: " + std::to_string(highscore));
				savehighscoredata(highscores);
				if (gameloopreturncode == 0)
				{
					quit = true;
				}
			}

			if (settings)
			{
				int settingsmenuretcode;
				settingsmenuretcode = settingsmenu(gamewindow, font);
				if (settingsmenuretcode == 2)
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
		gamewindow.draw(setbutton);
		gamewindow.display();
	}

	return returncode;
}