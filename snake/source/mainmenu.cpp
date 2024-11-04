#include "mainheader.h"
#include "mainmenuheader.h"

int screenreswidth = 800;
int screenresheight = 600;
bool fullscreen = false;
std::string defaultplayername = "placeholder";
bool askforcustomnameafteraround = true;

int mainmenurecalcbuttons(sf::Font& font, sf::Text& titletext, sf::Text& highscoretext, Button& playbutton, Button& quitbutton, Button& setbutton, sf::Sprite& mainmenugameicon, Button& logobox)
{
	titletext.setCharacterSize(TORELXPOS(40));
	titletext.setPosition(TORELXPOS(10), TORELYPOS(10));

	highscoretext.setCharacterSize(TORELXPOS(30));
	highscoretext.setPosition(TORELXPOS(10), TORELYPOS(550));

	playbutton.recalculatepos({ TORELXPOS(60),TORELYPOS(220) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	quitbutton.recalculatepos({ TORELXPOS(60),TORELYPOS(340) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	setbutton.recalculatepos({ TORELXPOS(60),TORELYPOS(280) }, { TORELXPOS(100),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	mainmenugameicon.setScale(sf::Vector2f(screenreswidth / 800.f, screenresheight / 600.f));
	mainmenugameicon.setPosition(sf::Vector2f(TORELXPOS(800-128), TORELYPOS(0)));

	logobox.recalculatepos({ TORELXPOS(800 - 64),TORELYPOS(64) }, { TORELXPOS(128),TORELYPOS(128) }, TORELXPOS(5));

	return 1;
}

int mainmenu(sf::RenderWindow& gamewindow)
{
	bool visitedsettingsyet = false;

	std::vector < std::pair<int, std::string>> highscores;
	std::vector <std::string> highscorenames;
	{
		std::vector<std::string> defaultsettings = { "800","600","0","0","placeholder","1" };
		if (loadhighscores(highscores, highscorenames) == -1)
		{
			return -1;
		}
		savehighscoredata(highscores);

		{ //set.txt
			std::vector<std::string> loadeddata = loadfromtxt("set.txt");
			if (loadeddata[0] == "ERROR")
			{
				savetotxt(defaultsettings, "set.txt"); //default settings ig
			}
			else {

				std::vector<int> checkfields = { 0,1,2,3,5 };

				std::vector<std::pair<int, int>> ranges;
				ranges.resize(loadeddata.size());

				ranges = { {400,7680},{300,4320},{0,1},{0,1},{-69,69},{0,1} };

				for (int i = 0; i < checkfields.size(); i++)
				{
					if (!is_int(loadeddata[checkfields[i]]))
					{
						if (errorboxyesno("Corrupted set.txt file.", "Data in set.txt is corrupted, and contains letters in places it should not. You can attempt to fix it manually. Do you want to reset to defaults?") == 1)
						{
							loadeddata = defaultsettings;
							savetotxt(loadeddata, "set.txt");
						}
						else {
							return -1;
						}
					}
				}

				for (int i = 0; i < ranges.size(); i++)
				{
					if (ranges[i].first == -69 && ranges[i].second == 69)
					{
						continue;
					}
					else {
						if (std::stoi(loadeddata[i]) < ranges[i].first || std::stoi(loadeddata[i]) > ranges[i].second)
						{
							if (errorboxyesno("Corrupted set.txt file.", "Data in set.txt is corrupted, certain values are outside the range they are supposed to be. You can attempt to fix it manually. Do you want to reset to defaults?") == 1)
							{
								loadeddata = defaultsettings;
								savetotxt(loadeddata, "set.txt");
							}
							else {
								return -1;
							}
						}
					}
				}
				screenreswidth = std::stoi(loadeddata[0]);
				screenresheight = std::stoi(loadeddata[1]);
				fullscreen = std::stoi(loadeddata[2]);
				visitedsettingsyet = std::stoi(loadeddata[3]);
				defaultplayername = loadeddata[4];
				askforcustomnameafteraround = std::stoi(loadeddata[5]);
			}
		}
	}

	bool quitfull = false;
	int returncode = 0;
	
	sf::Font font;
	if (!font.loadFromFile("rsc/munro.ttf"))
	{
		errorbox("Could not load font.", "Could not load munro.ttf in rsc folder. Try reinstalling your game or putting the font back.");
		return -1;
	}
	

	sf::Sprite mainmenugameicon;
	sf::Texture gameicontexture;
	if (!gameicontexture.loadFromFile("rsc/icon.png"))
	{
		errorbox("Could not load icon image.", "Could not load icon.png in rsc folder. Try reinstalling your game or putting the file back.");
		return -1;
	}

	mainmenugameicon.setTexture(gameicontexture);

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font);
	sf::Text highscoretext("Current highscore: None", font);
	if (highscores.size() > 0)
	{
		highscoretext.setString("Current highscore by " + highscorenames[0] + ": " + std::to_string(highscores[0].first));
	}

	Button playbutton(font, "Play");
	Button quitbutton(font, "Quit");
	Button setbutton(font, "Settings");
	Button logobox(font, " ");

	mainmenurecalcbuttons(font, titletext, highscoretext, playbutton, quitbutton, setbutton, mainmenugameicon, logobox);

	if (createwindow(gamewindow) == -1)
	{
		return -1;
	}

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
				if (windowevent.key.code == sf::Keyboard::Enter)
				{
					startgame = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Q)
				{
					quit = true;
				}
				else if (windowevent.key.code == sf::Keyboard::S)
				{
					settings = true;
				}
			}
			if (startgame)
			{
				int scorefromround = -1;
				std::string namefromround = "placeholder";
				gameloopreturncode = screenloopandinit(gamewindow, scorefromround, namefromround, font);
				loadhighscores(highscores, highscorenames);
				updatehighscores(highscores,highscorenames, scorefromround, namefromround);
				highscoretext.setString("Current highscore by " + highscorenames[0] + ": " + std::to_string(highscores[0].first));
				savehighscoredata(highscores);
				if (gameloopreturncode == 0)
				{
					quit = true;
				}
			}

			if (settings)
			{
				int settingsmenuretcode;
				settingsmenuretcode = settingsmenu(gamewindow, font, visitedsettingsyet);
				if (settingsmenuretcode == 0)
				{
					quit = true;
				}
				mainmenurecalcbuttons(font, titletext, highscoretext, playbutton, quitbutton, setbutton,mainmenugameicon, logobox);
			}

			if (quit)
			{
				gamewindow.close();
				returncode = 1;
				quitfull = true;
			}
		}

		gamewindow.clear(sf::Color(10, 10, 10, 255));
		gamewindow.draw(titletext);
		gamewindow.draw(highscoretext);
		gamewindow.draw(playbutton);
		gamewindow.draw(quitbutton);
		gamewindow.draw(setbutton);
		gamewindow.draw(mainmenugameicon);
		gamewindow.draw(logobox);
		gamewindow.display();
	}

	return returncode;
}