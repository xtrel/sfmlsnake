#include "mainheader.h"
#include <chrono>

int handleinput(sf::RenderWindow& gamewindow, std::pair<int,int>& snakeheading)
{
	sf::Event windowevent;
	while (gamewindow.pollEvent(windowevent))
	{
		if (windowevent.type == sf::Event::Closed)
		{
			gamewindow.close();
		}
		if (windowevent.type == sf::Event::KeyReleased)
		{
			if (windowevent.key.code == sf::Keyboard::Key::Up && snakeheading.second != 1)
			{
				snakeheading.first = 0;
				snakeheading.second = -1;
			}
			if (windowevent.key.code == sf::Keyboard::Key::Down && snakeheading.second != -1)
			{
				snakeheading.first = 0;
				snakeheading.second = 1;
			}
			if (windowevent.key.code == sf::Keyboard::Key::Right && snakeheading.first != -1)
			{
				snakeheading.first = 1;
				snakeheading.second = 0;
			}
			if (windowevent.key.code == sf::Keyboard::Key::Left && snakeheading.first != 1)
			{
				snakeheading.first = -1;
				snakeheading.second = 0;
			}
		}
		else
		{
			break;
		}
	}
	return 1;
}

int render(sf::RenderWindow &gamewindow, Mapstate &mapstate, std::pair<int, int>& apple, std::vector<std::pair<int, int>>& snakeparts)
{
	if (!(apple.first < 0 || apple.first > mapstate.mapxsize - 1 || apple.second < 0 || apple.second > mapstate.mapysize - 1))
	{
		mapstate.settilecolor(apple.first, apple.second, 1);
	}

	for (int i = 0; i < snakeparts.size(); i++)
	{
		mapstate.settilecolor(snakeparts[i].first, snakeparts[i].second, 3);
	}

	mapstate.transfermapstatetoVA(800, 600);

	gamewindow.clear();
	gamewindow.draw(mapstate);
	gamewindow.display();

	return 1;
}

int simulate(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple, std::vector<std::pair<int, int>> &snakeparts, std::pair<int, int> snakeheading, double& tillmove, double& movementcap, double& speed)
{
	if (apple.first == -1)
	{
		bool found = false;
		while (!found)
		{
			apple.first = rand() % mapstate.mapxsize;
			apple.second = rand() % mapstate.mapysize;
			
			bool checking = true;
			for (int i = 0; i < snakeparts.size(); i++)
			{
				if (apple.first == snakeparts[i].first && apple.second == snakeparts[i].second)
				{
					checking = false;
					break;
				}
			}
			if (checking)
			{
				found = true;
			}
		}
	}

	tillmove = tillmove + dt*speed;

	bool ate = false;
	bool wallcollide = false;

	if (tillmove > movementcap)
	{
		{
			std::pair<int, int> temphead;
			temphead.first = snakeparts[0].first + snakeheading.first;
			temphead.second = snakeparts[0].second + snakeheading.second;

			if(temphead.first < 0) wallcollide = true;
			if(temphead.second < 0) wallcollide = true;
			if(temphead.first > mapstate.mapxsize - 1) wallcollide = true;
			if(temphead.second > mapstate.mapysize - 1) wallcollide = true;

			for (int i = 2; i < snakeparts.size(); i++)
			{
				if (temphead.first == snakeparts[i].first && temphead.second == snakeparts[i].second)
				{
					wallcollide = true;
					break;
				}
			}
		}
		if (!wallcollide)
		{
			std::pair<int, int> oldhead = snakeparts[0];
			snakeparts[0].first += snakeheading.first;
			snakeparts[0].second += snakeheading.second;
			tillmove = 0;

			if (snakeparts[0].first == apple.first && snakeparts[0].second == apple.second)
			{
				ate = true;
			}

			if (!ate)
			{
				if (snakeparts.size() > 1)
				{
					mapstate.settilecolor(snakeparts[snakeparts.size() - 1].first, snakeparts[snakeparts.size() - 1].second, 0);
				}
				else
				{
					mapstate.settilecolor(oldhead.first, oldhead.second, 0);
				}

			}
			for (int i = 1; i < snakeparts.size(); i++)
			{
				std::pair<int, int> temppart = snakeparts[i];
				snakeparts[i] = oldhead;
				oldhead = temppart;
			}
			if (ate)
			{
				apple.first = -1;
				apple.second = -1;

				speed = speed - 0.01;

				snakeparts.push_back(oldhead);
			}
		}
	}

	if (wallcollide)
	{
		return 2;
	}


	return 1;
}

int screenloopandinit()
{
	Mapstate mapstate(16, 12);

	std::vector<std::pair<int, int>> snakeparts;
	std::pair<int, int> snakeheading = { 1,0 }; //speed vector in tiles per second
	snakeparts.push_back({ 0,0 });

	std::pair<int, int> apple = { -1, -1 };

	double t = 0.0;
	const double dt = 1.0/60.0;

	double tillmove = 0;
	double movementcap = dt*15;

	double speed = 1;

	double accumulator = 0.0;
	sf::Clock clock;

	//int framenum = 0;
	//int ticknum = 0;

	sf::RenderWindow gamewindow(sf::VideoMode(800, 600), "Snake", sf::Style::Close | sf::Style::Titlebar);
	//gamewindow.setVerticalSyncEnabled(true);

	while (gamewindow.isOpen())
	{
		sf::Time frameTime = clock.restart();
		accumulator = accumulator + frameTime.asSeconds();

		//std::cout << t << " " << framenum << " " << ticknum << " " << framenum / t << " " << ticknum / t << " " << accumulator << "\n";
		//std::cout << tillmove << " " << snakeheading.first << " " << snakeheading.second <<" "<<snakeparts[0].first<<" "<<snakeparts[0].second<< "\n";

		handleinput(gamewindow, snakeheading);

		while (accumulator >= dt)
		{
			//std::cout << "                                                      USED\n";
			int temp = simulate(mapstate, t, dt,apple,snakeparts, snakeheading, tillmove, movementcap,speed);
			if (temp == 2)
			{
				gamewindow.close();
			}

			accumulator = accumulator - dt;
			t = t + dt;
			//ticknum++;
		}
		//framenum++;
		render(gamewindow, mapstate,apple,snakeparts);
	}

	return 0;
}