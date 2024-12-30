#include <vector>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int updatehighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames, int currentscore, std::string namefromround);
int loadhighscores(std::vector < std::pair<int, std::string>>& highscores, std::vector <std::string>& highscorenames);
int savehighscoredata(std::vector < std::pair<int, std::string>>& highscores);
int createwindow(sf::RenderWindow& gamewindow);

int settingsmenu(sf::RenderWindow& gamewindow, sf::Font font,bool& visitedsettingsyet);
int leaderboardmenu(sf::RenderWindow& gamewindow, sf::Font font, std::vector < std::pair<int, std::string>> highscores, std::vector <std::string> highscorenames);

std::string getvtagfromstring(std::string instring);