#include "Game.h"

int main()
{
    //Srand
    srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Game game;

    //Loop voor de Game.
    while (game.GameRunning())
    {
        //Update
        game.update();
        //Render
        game.render();
    }

    return 0;
}

/*
To Do : 
-Quit button maken onder de restart button
-Button class aanmaken voor restart en quit 
-High scores laten zien van de best games
-
*/

/*
  Info :
   This-> : zodat je duidelijk kan zien wat deel uit maakt van de class en wat niet.

   mouseview : float sinds bijna heel het programma met floats werkt waardoor het makkelijker is.
*/