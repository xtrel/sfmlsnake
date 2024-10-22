#include "mainheader.h"
#include <chrono>

int handleinput(sf::RenderWindow& gamewindow)
{
	sf::Event windowevent;
	while (gamewindow.pollEvent(windowevent))
	{
		if (windowevent.type == sf::Event::Closed)
		{
			gamewindow.close();
		}
		else
		{
			break;
		}
	}

	return 1;
}

int render(sf::RenderWindow &gamewindow, Mapstate &mapstate)
{
	gamewindow.clear();
	gamewindow.draw(mapstate);
	gamewindow.display();

	return 1;
}

int simulate(Mapstate& mapstate)
{
	int ranx = rand() % 3;
	int rany = rand() % 3;
	int ranc = rand() % 4;
	mapstate.settilecolor(ranx, rany, ranc);
	mapstate.transfermapstatetoVA(800, 600);

	return 1;
}

int screenloopandinit()
{
	Mapstate mapstate(3, 3);

	double t = 0.0;
	const double dt = 0.00001;
	double accumulator = 0.0;
	sf::Clock clock;

	//int framenum = 0;
	//int ticknum = 0;

	sf::RenderWindow gamewindow(sf::VideoMode(800, 600), "Snake", sf::Style::Close | sf::Style::Titlebar);
	gamewindow.setVerticalSyncEnabled(true);

	while (gamewindow.isOpen())
	{
		sf::Time frameTime = clock.restart();
		accumulator = accumulator + frameTime.asSeconds();

		//std::cout << t << " " << framenum << " " << ticknum << " " << framenum / t << " " << ticknum / t << "\n";

		handleinput(gamewindow);

		while (accumulator >= dt)
		{
			simulate(mapstate);

			accumulator = accumulator - dt;
			t = t + dt;
			//ticknum++;
		}
		//framenum++;
		render(gamewindow, mapstate);
	}

	return 0;
}