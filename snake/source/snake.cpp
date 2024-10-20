#include "mainheader.h"

int main(int argc, char* args[])
{
    sf::RenderWindow gamewindow;

    srand(time(0));

    writetolog("hello");

    mainmenu(gamewindow);

    return 0;
}
