#include "mainheader.h"

int main(int argc, char* args[])
{
    sf::RenderWindow gamewindow;

    srand(time(0));

    savetodatatxt({ "ad" });

    mainmenu(gamewindow);

    return 0;
}
