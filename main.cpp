#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    game.init();

    while (game.isRunning())
    {
        game.processInput();
        game.update();
        game.render();
    }

    return 0;
}