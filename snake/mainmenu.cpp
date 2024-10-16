#include "mainheader.h"

int mainmenu(sf::RenderWindow& gamewindow)
{
	sf::Font font;
	font.loadFromFile("rsc/coolvetica rg.otf");

	gamewindow.create(sf::VideoMode(800, 600), "Snake " + versiontag, sf::Style::Close | sf::Style::Titlebar);
	{
		sf::Image icon;
		icon.loadFromFile("rsc/icon.png");
		gamewindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	bool quit = false;
	int returncode = 0;

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font, 40);
	titletext.setPosition(10, 0);

	Button playbutton(font, "Play", { 60,200 }, { 100,50 }, 5, 25);
	playbutton.buttonedgeupdate();
	playbutton.buttontextupdate();

	Button quitbutton(font, "Quit", { 60,260 }, { 100,50 }, 5, 25);
	quitbutton.buttonedgeupdate();
	quitbutton.buttontextupdate();

	while (!quit)
	{
		int gameloopreturncode = 0;
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			if (windowevent.type == sf::Event::Closed)
			{
				gamewindow.close();
				returncode = 1;
				quit = true;
			}
			if (windowevent.type == sf::Event::MouseButtonReleased)
			{
				if (playbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					gameloopreturncode = screenloopandinit(gamewindow);
					if (gameloopreturncode == 0)
					{
						gamewindow.close();
						returncode = 1;
						quit = true;
					}
				}
				else if (quitbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					gamewindow.close();
					returncode = 1;
					quit = true;
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter || windowevent.key.code == sf::Keyboard::Space)
				{
					gameloopreturncode = screenloopandinit(gamewindow);
					if (gameloopreturncode == 0)
					{
						gamewindow.close();
						returncode = 1;
						quit = true;
					}
				}
				else if (windowevent.key.code == sf::Keyboard::Q)
				{
					gamewindow.close();
					returncode = 1;
					quit = true;
				}
			}
		}

		gamewindow.clear();
		gamewindow.draw(titletext);
		gamewindow.draw(playbutton);
		gamewindow.draw(quitbutton);
		gamewindow.display();
	}

	return returncode;
}