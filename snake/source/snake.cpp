#include "mainheader.h"
#include "tinyfiledialogs.h"

int main(int argc, char* args[])
{
    sf::RenderWindow gamewindow;

    srand(time(0));
    
    //std::cout << tinyfd_messageBox(NULL, "Message", "ok", "error", 1);

    mainmenu(gamewindow);

    return 0;
}
