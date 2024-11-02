#include "mainheader.h"
#include "mainmenuheader.h"

int settingsmenurecalcbuttons(sf::Font& font, Button& backtomenubutton, Button& fullscreenbutton, Button& changeresbutton, std::vector<Button>& resolutionbuttons)
{
	backtomenubutton.recalculatepos({ TORELXPOS(100),TORELYPOS(600 - 35) }, { TORELXPOS(180),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	fullscreenbutton.recalculatepos({ TORELXPOS(87.5),TORELYPOS(35) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	changeresbutton.recalculatepos({ TORELXPOS(107.5),TORELYPOS(95) }, { TORELXPOS(200),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	for (int i = 0; i < resolutionbuttons.size(); i++)
	{
		resolutionbuttons[i].recalculatepos({TORELXPOS(400),TORELYPOS(35 + i * 60)}, {TORELXPOS(150),TORELYPOS(50)}, TORELXPOS(2.5), TORELXPOS(20));
	}
	return 1;
}

int settingsmenu(sf::RenderWindow& gamewindow, sf::Font font)
{
	gamewindow.clear();

	bool quitfull = false;
	bool drawresolutionchoices = false;

	Button backtomenubutton(font, "Back to menu");
	Button fullscreenbutton(font, "Fullscreen: notloaded");
	Button changeresbutton(font, "Change resolution");

	std::vector<Button> resolutionbuttons;
	std::vector<std::pair<int, int>> resolutions = { {800,600},{1600,1200},{1920,1080},{3840,2160} };
	for (int i = 0; i < resolutions.size(); i++)
	{
		resolutionbuttons.push_back(Button(font, "W" + std::to_string(resolutions[i].first) + "x" + std::to_string(resolutions[i].second) + "H"));
	}

	settingsmenurecalcbuttons(font, backtomenubutton, fullscreenbutton, changeresbutton, resolutionbuttons);

	while (!quitfull)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			bool backtomenu = false;
			bool quitgame = false;
			bool resetwindow = false;
			if (windowevent.type == sf::Event::Closed)
			{
				quitgame = true;
			}
			if (windowevent.type == sf::Event::MouseButtonReleased)
			{
				if (backtomenubutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					backtomenu = true;
				}
				if (fullscreenbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					fullscreen = !fullscreen;
					resetwindow = true;
				}
				if (changeresbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					drawresolutionchoices = !drawresolutionchoices;
				}
				if (drawresolutionchoices)
				{
					for (int i = 0; i < resolutionbuttons.size(); i++)
					{
						if (resolutionbuttons[i].arethosethisbuttoncords({sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y}))
						{
							screenreswidth = resolutions[i].first;
							screenresheight = resolutions[i].second;
							resetwindow = true;
						}
					}
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					quitgame = true;
				}
			}
			
			if (resetwindow)
			{
				createwindow(gamewindow);
				settingsmenurecalcbuttons(font, backtomenubutton, fullscreenbutton, changeresbutton, resolutionbuttons);
			}

			if (quitgame || backtomenu)
			{
				std::vector<std::string> savevec;
				savevec.push_back(std::to_string(screenreswidth));
				savevec.push_back(std::to_string(screenresheight));
				savevec.push_back(std::to_string(fullscreen));
				savetotxt(savevec,"set.txt");
			}

			if (quitgame)
			{
				return 0;
			}

			if (backtomenu)
			{
				return 1;
			}
		}

		if (fullscreen)
		{
			fullscreenbutton.buttonstring = "Fullscreen: on";
		}
		else {
			fullscreenbutton.buttonstring = "Fullscreen: off";
		}
		fullscreenbutton.buttontextupdate();

		gamewindow.clear();
		gamewindow.draw(backtomenubutton);
		gamewindow.draw(fullscreenbutton);
		gamewindow.draw(changeresbutton);
		if (drawresolutionchoices)
		{
			for (int i = 0; i < resolutionbuttons.size(); i++)
			{
				Button tempbutton = resolutionbuttons[i];
				gamewindow.draw(tempbutton); //sfml for some reason does not like drawing straight from a vector
			}
		}
		gamewindow.display();
	}
}