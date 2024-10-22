#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //combined with windows subsystem in project settings, linker, system, makes no console

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>

const std::string versiontag = "V1.0.1.2";

int screenloopandinit();

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

	std::vector<std::vector<std::vector<int>>> mapstate; // mapstate[x][y][channel] 0-r 1-g 2-b 3-a

	int mapxsize, mapysize;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices);
	}

	sf::VertexArray vertices;
};