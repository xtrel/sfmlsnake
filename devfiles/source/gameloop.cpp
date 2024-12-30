#include "mainheader.h"
#include <chrono>
#include <string>

int handleinput(sf::RenderWindow& gamewindow)
{
	sf::Event windowevent;

	while (gamewindow.pollEvent(windowevent))
	{
		if (windowevent.type == sf::Event::Closed)
		{
			return 2;
		}
		if (windowevent.type == sf::Event::KeyReleased)
		{
			if (windowevent.key.code == sf::Keyboard::Q)
			{
				return 2;
			}
			else if (windowevent.key.code == sf::Keyboard::B)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
				{
					return 3;
				}
			}
		}
	}

	return 1;
}

int render(sf::RenderWindow &gamewindow, Mapstate &mapstate, std::pair<int, int>& apple, std::vector<std::pair<int, int>>& snakeparts,std::pair<int, int>& snakeheading,
	sf::Text text, sf::Font font, double& tillmove, const double movementcap)
{
	mapstate.fillmapstatewithrgb(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, backgroundcolor.a);

	if (!(apple.first < 0 || apple.first > mapstate.mapxsize - 1 || apple.second < 0 || apple.second > mapstate.mapysize - 1))
	{
		mapstate.settilecolor(apple.first, apple.second, 1);
	}
	/*
	int valr = 255 - 1;
	int valg = 255 - 1;
	int valb = 0;
	for (int i = 1; i < snakeparts.size(); i++)
	{
		
		if (i %  2 == 0)
		{
			valr = 255-i;
			valg = 255-i;
			valb = 0;
		}
		else if (i % 2 == 1)
		{
			valr = 2*i;
			valg = 192-2*i;
			valb = 0;
		}
		mapstate.settilecolorRGB(snakeparts[i].first, snakeparts[i].second, valr, valg, valb, 255);
	}
	*/
	/*
	for (int i = 1; i < snakeparts.size(); i++)
	{
		double val = abs(abs(255 * sin((i + 50) / 25.f)) - i / 5.f);
		mapstate.settilecolorRGB(snakeparts[i].first, snakeparts[i].second, 25, 25, floor(val), 255);
	}
	*/
	{
		for (int i = 1; i < snakeparts.size(); i++)
		{
			double valb = abs(abs(255 * sin((3 * i + 70) / 25.f)) - 2 * i / 5.f);
			double valg = abs(abs(255 * cos((3 * i / 3.f + 65) / 25.f)) - 1.5f * i / 5.f);
			double valr = abs(abs(255 * sin((4 * i + 70) / 25.f)) - 2 * i / 5.f);
			mapstate.settilecolorRGB(snakeparts[i].first, snakeparts[i].second, floor(valr / 3.5f), floor(valg / 2.f), floor(valb), 255);
		}

		mapstate.settilecolorRGB(snakeparts[0].first, snakeparts[0].second, 140, 140, 140, 255);
		mapstate.transfermapstatetoVA(screenreswidth, screenresheight);

	}

	gamewindow.clear();
	gamewindow.draw(mapstate);
	gamewindow.draw(text);
	gamewindow.display();

	return 1;
}

int simulate(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple, std::vector<std::pair<int, int>> &snakeparts, std::pair<int, int>& snakeheading,
	double& tillmove,const double movementcap, double& speed, sf::Text& text)
{
	if (snakeparts.size() >= 192)
	{
		return 3;
	}

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

	int truesnakesize = snakeparts.size() + 1;

	{
		int right = 0;
		int up = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			up = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			up = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			right = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			right = -1;
		}

		if (right == 1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].first >= snakeparts[1].first)
				{
					snakeheading.first = 1;
					snakeheading.second = 0;
				}
			}
			else {
				snakeheading.first = 1;
				snakeheading.second = 0;
			}
		}
		if (right == -1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].first <= snakeparts[1].first)
				{
					snakeheading.first = -1;
					snakeheading.second = 0;
				}
			}
			else {
				snakeheading.first = -1;
				snakeheading.second = 0;
			}
		}
		if (up == 1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].second <= snakeparts[1].second)
				{
					snakeheading.first = 0;
					snakeheading.second = -1;
				}
			}
			else {
				snakeheading.first = 0;
				snakeheading.second = -1;
			}
		}
		if (up == -1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].second >= snakeparts[1].second)
				{
					snakeheading.first = 0;
					snakeheading.second = 1;
				}
			}
			else {
				snakeheading.first = 0;
				snakeheading.second = 1;
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

				//V1.1.0.0 speed = speed + ((snakeparts.size() + 3) / snakeparts.size() - snakeparts.size() / 100) * 0.05;

				speed = (-pow((0.013 * truesnakesize), 2)) + (truesnakesize / 25.0f) + 1.0f;

				int temp = snakeparts.size();
				std::string speedstring = std::to_string(speed);
				speedstring = speedstring.substr(0, 4);

				text.setString("Points:" + std::to_string(truesnakesize) + " Speed:" + speedstring);

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

int screenloopandinit(sf::RenderWindow& gamewindow, int& score,std::string& name, sf::Font font)
{
	Mapstate mapstate(16, 12);

	std::vector<std::pair<int, int>> snakeparts;
	std::pair<int, int> snakeheading = { 1,0 }; //speed vector in tiles per second
	snakeparts.push_back({ 0,0 });

	std::pair<int, int> apple = { -1, -1 };

	double t = 0.0;
	const double dt = 1 / (128.0f);

	double tillmove = 0;
	const double movementcap = (1 / 64.0f) * 15;

	/*
	const double dt = (1.0 / 64.0) / 4;
	0.00390625

	movement cap 0.234375

	double tillmove = 0;
	double movementcap = dt * 15*4;
	*/

	double speed = 1;

	double accumulator = 0.0;
	sf::Clock clock;

	//int framenum = 0;
	//int ticknum = 0;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(TORELXPOS(30));
	text.setFillColor(sf::Color::White);
	text.setString("Welcome to snake\nBy Hubert Gonera\n" + versiontag);

	gamewindow.setVerticalSyncEnabled(true);

	bool lost = false;
	bool won = false;
	bool quit = false;
	bool backtomenu = false;

	while (!lost && !won && !quit && !backtomenu)
	{
		int temp = 0;;
		sf::Time frameTime = clock.restart();
		accumulator = accumulator + frameTime.asSeconds();

		//std::cout << t << " " << framenum << " " << ticknum << " " << framenum / t << " " << ticknum / t << " " << accumulator << "\n";
		//std::cout << tillmove << " " << snakeheading.first << " " << snakeheading.second <<" "<<snakeparts[0].first<<" "<<snakeparts[0].second<< "\n";

		temp = handleinput(gamewindow);
		if (temp == 2)
		{
			quit = true;
		}
		if (temp == 3)
		{
			backtomenu = true;
		}

		while (accumulator >= dt)
		{
			//std::cout << "                                                      USED\n";
			temp = simulate(mapstate, t, dt, apple, snakeparts, snakeheading, tillmove, movementcap, speed, text);
			if (temp == 2)
			{
				lost = true;
			}
			if (temp == 3)
			{
				won = true;
			}

			accumulator = accumulator - dt;
			t = t + dt;
			//ticknum++;
		}
		//framenum++;
		render(gamewindow, mapstate, apple, snakeparts,snakeheading, text, font, tillmove,movementcap);
	}

	score = snakeparts.size();

	if (quit)
	{
		return 0;
	}

	if (backtomenu)
	{
		return 3;
	}

	int retcode = -1;

	if (won)
	{
		text.setString("Won!");
		retcode = 1;
	}
	if (lost)
	{
		text.setString("Lost!");
		retcode = 2;
	}

	text.setCharacterSize(TORELXPOS(60));
	{
		sf::FloatRect textrect = text.getLocalBounds();
		int h = textrect.height;
		int w = textrect.width;
		text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
		text.setPosition(sf::Vector2f(TORELXPOS(400), TORELYPOS(300)));
	}

	gamewindow.draw(text);
	gamewindow.display();

	sf::Clock endclock;
	sf::Time elapsed;

	elapsed = endclock.getElapsedTime();

	bool go = false;
	bool skipask = false;

	while (elapsed.asSeconds() <= 7 && !go)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			if (windowevent.type == sf::Event::Closed)
			{
				retcode = 0;
				go = true;
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter)
				{
					go = true;
				}
				if (windowevent.key.code == sf::Keyboard::Space)
				{
					go = true;
					skipask = true;
				}
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					retcode = 0;
					go = true;
				}
			}
		}
		elapsed = endclock.getElapsedTime();
	}

	if (retcode == 0)
	{
		return retcode;
	}

	bool quitgame = false;
	if (askforcustomnameafteraround && !skipask)
	{
		std::string playername = getstringfromplayermenu(font, gamewindow, quitgame);
		name = playername;
		if (quitgame)
		{
			return 0;
		}
	}
	else if (askforcustomnameafteraround && skipask)
	{
		name = defaultplayername;
	}
	else if(!askforcustomnameafteraround)
	{
		name = "NOT-SET";
	}

	return retcode;
}