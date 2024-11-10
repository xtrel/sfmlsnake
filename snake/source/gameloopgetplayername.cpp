#include "mainheader.h"

std::string getstringfromplayermenu(sf::Font font, sf::RenderWindow& gamewindow, bool& quitgame,std::string msgstring)
{
	sf::Text text;
	text.setFont(font);
	text.setString(msgstring);
	text.setCharacterSize(TORELXPOS(40));
	{
		sf::FloatRect textrect = text.getLocalBounds();
		int h = textrect.height;
		int w = textrect.width;
		text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
		text.setPosition(sf::Vector2f(TORELXPOS(400), TORELYPOS(100)));
	}

	sf::Text playertext;
	playertext.setFont(font);
	playertext.setString("");
	playertext.setCharacterSize(TORELXPOS(40));

	Button warningbutton(font, "");
	warningbutton.recalculatepos({ TORELXPOS(400),TORELYPOS(300) }, { TORELXPOS(800), TORELYPOS(600) }, TORELXPOS(10), TORELXPOS(25));

	bool choosing = true;
	std::string playerinput = "";

	while (choosing)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			if (windowevent.type == sf::Event::TextEntered)
			{
				char inputchar = windowevent.text.unicode;
				if (std::isprint(inputchar) && playerinput.size()<28 && inputchar != ';')
				{
					playerinput += inputchar;
				}
			}
			else if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::BackSpace)
				{
					if (playerinput.size() > 0)
					{
						playerinput.pop_back();
					}
				}
				if (windowevent.key.code == sf::Keyboard::Enter)
				{
					if (playerinput.size() == 0)
					{
						playerinput = defaultplayername;
					}
					choosing = false;
				}
			}
			if (windowevent.type == sf::Event::Closed)
			{
				quitgame = true;
				if (playerinput.size() == 0)
				{
					playerinput = defaultplayername;
				}
				choosing = false;
			}
		}
		gamewindow.clear(sf::Color(10, 10, 10, 255));
		{
			playertext.setString(playerinput);
			sf::FloatRect textrect = text.getLocalBounds();
			int h = textrect.height;
			int w = textrect.width;
			playertext.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
			playertext.setPosition(sf::Vector2f(TORELXPOS(400), TORELYPOS(300)));
		}
		gamewindow.draw(playertext);
		gamewindow.draw(text);
		gamewindow.draw(warningbutton);
		gamewindow.display();
	}
	return playerinput;
}