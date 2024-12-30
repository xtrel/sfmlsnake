#include "mainheader.h"
#include "mainmenuheader.h"

int recalcleaderboardmenu(Button& backtomenubutton, Button& highscoreframe, Button& downbutton, Button& upbutton, Button& shownhighscores)
{
	backtomenubutton.recalculatepos({ TORELXPOS(100),TORELYPOS(35) }, { TORELXPOS(180),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	highscoreframe.recalculatepos({ TORELXPOS(400),TORELYPOS(300 + (35 + 20) / 2) }, { TORELXPOS(800 - 20),TORELYPOS(600 - 35 - 10 - 10 - 20) }, TORELXPOS(5));

	downbutton.recalculatepos({ TORELXPOS(757.5),TORELYPOS(100+38*12) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(15));
	upbutton.recalculatepos({ TORELXPOS(757.5),TORELYPOS(100 + 38 * 0) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(15));
	shownhighscores.recalculatepos({ TORELXPOS(757.5),TORELYPOS((100 + 38 * 0 + 100 + 38*12)/2) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(0), TORELXPOS(15));

	return 1;
}

int leaderboardmenu(sf::RenderWindow& gamewindow, sf::Font font, std::vector < std::pair<int, std::string>> highscores, std::vector <std::string> highscorenames)
{
	gamewindow.clear();

	bool quitfull = false;

	int drawto = 13;
	int drawfrom = 0;

	Button backtomenubutton(font, "Back to menu");
	Button highscoreframe(font, " ");

	Button downbutton(font, "\\/");
	Button upbutton(font, "/\\");
	Button shownhighscores(font, "NULL");

	std::vector<Button> highscorebuttonsname;
	std::vector<Button> highscorebuttonshighscore;
	std::vector<Button> highscorebuttonstag;

	for (int i = 0; i < highscores.size(); i++)
	{
		highscorebuttonsname.push_back(Button(font, highscorenames[i], { TORELXPOS(370 / 2 + 25),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(370),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
		highscorebuttonshighscore.push_back(Button(font, std::to_string(highscores[i].first), { TORELXPOS(370 + 25 + 90 / 2 - 5),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(90),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
		std::string temptagstring = highscores[i].second;
		std::reverse(temptagstring.begin(), temptagstring.end());
		size_t pos = temptagstring.find(';');
		if (pos == std::string::npos)
		{
			highscorebuttonsname.pop_back();
			highscorebuttonshighscore.pop_back();
			continue;
		}
		else {
			temptagstring = temptagstring.substr(0, pos);
			std::reverse(temptagstring.begin(), temptagstring.end());
		}
		highscorebuttonstag.push_back(Button(font, temptagstring, { TORELXPOS(370 + 25 + 90 - 10 + 250 / 2),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(250),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
	}
	recalcleaderboardmenu(backtomenubutton, highscoreframe,downbutton,upbutton,shownhighscores);

	while (!quitfull)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			bool backtomenu = false;
			bool quitgame = false;
			bool resetwindow = false;
			bool goup = false;
			bool godown = false;
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
				if (downbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					godown = true;
				}
				if (upbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					goup = true;
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					quitgame = true;
				}
				else if (windowevent.key.code == sf::Keyboard::B)
				{
					backtomenu = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Up)
				{
					goup = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Down)
				{
					godown = true;
				}
			}

			if (godown)
			{
				if (highscorebuttonsname.size() > 13)
				{
					if (drawto < highscorebuttonsname.size())
					{
						drawfrom++;
						drawto++;
					}
				}
			}

			if (goup)
			{
				if (highscorebuttonsname.size() > 13)
				{
					if (drawfrom > 0)
					{
						drawfrom--;
						drawto--;
					}
				}
			}

			if (quitgame || backtomenu)
			{

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

		gamewindow.clear(backgroundcolor);
		gamewindow.draw(backtomenubutton);
		gamewindow.draw(highscoreframe);
		sf::Transform buttonoffset;
		buttonoffset.translate(sf::Vector2f(0, -TORELYPOS(38 * drawfrom)));
		for (int i = drawfrom; i < drawto && i < highscorebuttonsname.size(); i++)
		{
			if (highscorebuttonsname.size() > 0 && highscorebuttonshighscore.size() > 0 && highscorebuttonstag.size() > 0)
			{
				Button tempbutton = highscorebuttonsname[i];
				gamewindow.draw(tempbutton, buttonoffset);
				tempbutton = highscorebuttonshighscore[i];
				gamewindow.draw(tempbutton, buttonoffset);
				tempbutton = highscorebuttonstag[i];
				gamewindow.draw(tempbutton, buttonoffset);
			}
		}
		gamewindow.draw(upbutton);
		gamewindow.draw(downbutton);

		{
			std::string range;

			if (highscorebuttonsname.size() == 0)
			{
				range = "0-0";
			}
			else if (highscorebuttonsname.size() < 14)
			{
				range = "1-" + std::to_string(highscorebuttonsname.size());
			}
			else {
				range = std::to_string(drawfrom + 1) + "-" + std::to_string(drawto);
			}

			shownhighscores.buttonstring = range;
		}
		shownhighscores.buttontextupdate();

		gamewindow.draw(shownhighscores);
		gamewindow.display();
	}
	return -1;
}