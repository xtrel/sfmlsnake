#include "mainheader.h"
#include "mainmenuheader.h"

int settingsmenu(sf::RenderWindow& gamewindow, sf::Font font)
{
	gamewindow.clear();

	bool quitfull = false;

	Button backtomenubutton(font, "Back to menu", { TORELXPOS(100),TORELYPOS(600 - 35) }, { TORELXPOS(180),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	Button fullscreenbutton(font, "Fullscreen: notloaded", { TORELXPOS(87.5),TORELYPOS(35) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	while (!quitfull)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			bool backtomenu = false;
			bool quitgame = false;
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
					if (fullscreen)
					{
						fullscreen = false;
					}
					else {
						fullscreen = true;
					}
					createwindow(gamewindow);
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					quitgame = true;
				}
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
				return 2;
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
		gamewindow.display();
	}
}