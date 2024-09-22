#include "Game.h"

int main()
{
    //Srand
    srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Game game;

    //Loop voor de Game.
    while (game.GameRunning() && game.getendgame() == false)
    {
        //Update
        game.update();
        //Render
        game.render();
    }

    return 0;
}



