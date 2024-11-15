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
* Abstraction : abastract class -> at least 1 pure virtual function = '= 0'.
*               bv. vector -> je hoeft niet te weten hoe het intern werkt,
*               je gebruikt gewoon push_back(),size(),...
* 
* Object Composistion : game class heeft andere classes die hun eigen objecten bevatten
*                       zoals : TextClass, Buttons en Highscores zitten deze classes in de Game class.
* 
* Encapsulation : public,private,...
*/