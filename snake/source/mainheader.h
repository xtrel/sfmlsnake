#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //combined with windows subsystem in project settings, linker, system, makes no console

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>

const std::string versiontag = "Vdev";
const std::string builddate = "Ddev";

extern int screenreswidth;
extern int screenresheight;
extern bool fullscreen;

int mainmenu(sf::RenderWindow& gamewindow);

int screenloopandinit(sf::RenderWindow& gamewindow, int& score);

std::vector<std::string> loadfromtxt(std::string filename = "data.txt");
bool writetolog(std::string text, std::string path = "log.txt");
int savetotxt(std::vector<std::string> datavector, std::string filename = "data.txt");

int TORELXPOS(double pos);
int TORELYPOS(double pos);
int TORELSIZE(double pos);

class Mapstate : public sf::Drawable
{
public:

	Mapstate(int _mapxsize, int _mapysize)
	{
		mapxsize = _mapxsize;
		mapysize = _mapysize;
		
		vertices.setPrimitiveType(sf::Triangles);
		vertices.resize(mapxsize * mapysize * 6);

		{
			std::vector< std::vector<std::vector<int>>> tempx;
			for (int x = 0; x < mapxsize; x++)
			{
				std::vector<std::vector<int>> tempy;
				for (int y = 0; y < mapysize; y++)
				{
					tempy.push_back({0,0,0,255});
				}
				tempx.push_back(tempy);
			}
			mapstate = tempx;
		}
	}

	int loadmapstateasrgb(std::vector<std::vector<std::vector<int>>> loadedmapstatevector)
	{
		for (int x = 0; x < mapxsize; x++)
		{
			for (int y = 0; y < mapysize; y++)
			{
				for (int c = 0; c < 4; c++)
				{
					mapstate[x][y][c] = loadedmapstatevector[x][y][c];
				}
			}
		}
		return 1;
	}

	int loadmapstateascustom(std::vector<std::vector<int>> loadedmapstatevector)
	{
		for (int x = 0; x < mapxsize; x++)
		{
			for (int y = 0; y < mapysize; y++)
			{
				if (loadedmapstatevector[x][y] == 0)
				{
					mapstate[x][y] = { 0,0,0,255 };
				}
				else if (loadedmapstatevector[x][y] == 1)
				{
					mapstate[x][y] = { 255,0,0,255 };
				}
				else if (loadedmapstatevector[x][y] == 2)
				{
					mapstate[x][y] = { 0,255,0,255 };
				}
				else if (loadedmapstatevector[x][y] == 3)
				{
					mapstate[x][y] = { 0,0,255,255 };
				}
			}
		}
		return 1;
	}

	int fillmapstatewithrgb(int r, int g, int b, int a)
	{
		for (int x = 0; x < mapxsize; x++)
		{
			for (int y = 0; y < mapysize; y++)
			{
				mapstate[x][y] = { r,g,b,a };
			}
		}
		return 1;
	}

	void outputmapstatetoconsole()
	{
		for (int x = 0; x < mapxsize; x++)
		{
			for (int y = 0; y < mapysize; y++)
			{
				for (int c = 0; c < 4; c++)
				{
					std::cout << mapstate[x][y][c] << ",";
				}
				std::cout << " ";
			}
			std::cout << "\n";
		}
	}

	int transfermapstatetoVA(int screenwidth, int screenheight)
	{
		sf::Vector2u tileSize;
		tileSize.x = screenwidth / mapxsize;
		tileSize.y = screenheight / mapysize;

		for (int x = 0; x < mapxsize; x++)
		{
			for (int y = 0; y < mapysize; y++)
			{
				int tilenumber = x + y * mapxsize;


				sf::Vertex* triangles = &vertices[(x + y * mapxsize) * 6];

				sf::Color mapstatecolor = sf::Color(mapstate[x][y][0], mapstate[x][y][1], mapstate[x][y][2], mapstate[x][y][3]);

				for (int i = 0; i < 6; i++)
				{
					triangles[i].color = mapstatecolor;
				}

				triangles[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
				triangles[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
				triangles[2].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
				triangles[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
				triangles[4].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
				triangles[5].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
			}
		}
		return 1;
	}

	int settilecolor(int x, int y, int color)
	{
		if (x > mapxsize-1 || x < 0 || y < 0 || y > mapysize-1)
		{
			return -1;
		}
		if (color == 0)
		{
			mapstate[x][y] = { 0,0,0,255 };
		}
		else if (color == 1)
		{
			mapstate[x][y] = { 255,0,0,255 };
		}
		else if (color == 2)
		{
			mapstate[x][y] = { 0,255,0,255 };
		}
		else if (color == 3)
		{
			mapstate[x][y] = { 0,0,255,255 };
		}
		else { return -1; }
		return 1;
	}

	int settilecolorRGB(int x, int y, int r, int g, int b, int a)
	{
		mapstate[x][y] = { r,g,b,a };
		return 1;
	}

	std::vector<std::vector<std::vector<int>>> mapstate; // mapstate[x][y][channel] 0-r 1-g 2-b 3-a

	int mapxsize, mapysize;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices);
	}

	sf::VertexArray vertices;
};

class Button : public sf::Drawable
{
public:
	
	Button(sf::Font font, std::string string = "Default", std::pair<int, int> screenpos = { 10,10 }, std::pair<int, int> screensize = { 5,5 }, int borderw = 5, int fontsize = 10)
	{
		buttonstring = string;
		buttonfont = font;

		buttonscreenpos = screenpos;
		buttonscreensize = screensize;

		buttonfontsize = fontsize;

		borderwidth = borderw;

		vertices.setPrimitiveType(sf::TriangleStrip);
		vertices.resize(10);

		vertices[0].color = sf::Color::White;
		vertices[1].color = sf::Color::White;
		vertices[2].color = sf::Color::White;
		vertices[3].color = sf::Color::White;
		vertices[4].color = sf::Color::White;
		vertices[5].color = sf::Color::White;
		vertices[6].color = sf::Color::White;
		vertices[7].color = sf::Color::White;
		vertices[8].color = sf::Color::White;
		vertices[9].color = sf::Color::White;

	}

	int buttonedgeupdate()
	{
		int w = borderwidth;
		int xpos = buttonscreenpos.first;
		int ypos = buttonscreenpos.second;
		int xsiz = buttonscreensize.first/2;
		int ysiz = buttonscreensize.second/2;

		vertices[0].position = sf::Vector2f(xpos - xsiz, ypos - ysiz);
		vertices[1].position = sf::Vector2f(xpos - xsiz + w, ypos - ysiz + w);
		vertices[2].position = sf::Vector2f(xpos + xsiz, ypos - ysiz);
		vertices[3].position = sf::Vector2f(xpos + xsiz - w, ypos - ysiz + w);
		vertices[4].position = sf::Vector2f(xpos + xsiz, ypos + ysiz);
		vertices[5].position = sf::Vector2f(xpos + xsiz - w, ypos + ysiz - w);
		vertices[6].position = sf::Vector2f(xpos - xsiz, ypos + ysiz);
		vertices[7].position = sf::Vector2f(xpos - xsiz + w, ypos + ysiz - w);
		vertices[8].position = vertices[0].position;
		vertices[9].position = vertices[1].position;

		return 1;
	}

	int buttontextupdate()
	{
		buttontext.setFont(buttonfont);
		buttontext.setCharacterSize(buttonfontsize);
		buttontext.setString(buttonstring);

		sf::FloatRect textrect = buttontext.getLocalBounds();
		buttontext.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
		buttontext.setPosition(buttonscreenpos.first, buttonscreenpos.second);

		return 1;
	}

	bool arethosethisbuttoncords(std::pair<int,int> presscords)
	{
		int w = borderwidth;
		int xpos = buttonscreenpos.first;
		int ypos = buttonscreenpos.second;
		int xsiz = buttonscreensize.first / 2;
		int ysiz = buttonscreensize.second / 2;

		if (presscords.first >= xpos + xsiz - w)
		{
			return false;
		}
		if (presscords.first <= xpos - xsiz + w)
		{
			return false;
		}
		if (presscords.second <= ypos - ysiz + w)
		{
			return false;
		}
		if (presscords.second >= ypos + ysiz - w)
		{
			return false;
		}

		return true;
	}

	std::string buttonstring;

	int borderwidth;
	int buttonfontsize;

	std::pair<int, int> buttonscreenpos;
	std::pair<int, int> buttonscreensize;

private:
	
	sf::Text buttontext;
	sf::Font buttonfont;

	sf::VertexArray vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices);
		target.draw(buttontext);
		//target.draw();
	}
};