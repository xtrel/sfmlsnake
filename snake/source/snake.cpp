#include "mainheader.h"

int main(int argc, char* args[])
{
    sf::RenderWindow gamewindow;

    srand(time(0));
   
    int mainmenuretint = -1;

    mainmenuretint = mainmenu(gamewindow);

    return mainmenuretint;
}
