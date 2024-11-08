#pragma once
#include "mainheader.h"

int updatehighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames, int currentscore, std::string namefromround);
int loadhighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames);
int savehighscoredata(std::vector < std::pair<int, std::string>>& highscores);
int createwindow(sf::RenderWindow& gamewindow);

int settingsmenu(sf::RenderWindow& gamewindow, sf::Font font,bool& visitedsettingsyet);