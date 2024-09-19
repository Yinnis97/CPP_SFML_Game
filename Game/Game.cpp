#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GameFunctions.hpp"
#include "Classes.hpp"

using namespace sf; //hoef ik niet overal sf:: voor te zetten.


int main()
{
    VideoMode desktop = VideoMode::getDesktopMode();
    RenderWindow window(desktop, "Game V1.0", Style::None);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
  

    // Create background object
    Background background("Textures/background.png", window);

    // Create spaceship object
    Spaceship spaceship("Textures/Spaceship.png", window);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        Update(spaceship, window);
        Draw(window, spaceship, background);

    }

    return 0;
}



