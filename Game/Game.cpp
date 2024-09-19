#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

using namespace sf; //hoef ik niet overal sf:: voor te zetten.

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Game V1.0");
    window.setFramerateLimit(60);

    CircleShape circle(20.f);
    circle.setFillColor(Color::Blue);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //Update
        

        //Clear : Moet gebeuren vor telkens een nieuwe versie van de display te krijgen.
        window.clear(); 

        //Draw the updated version.
        window.draw(circle);
     
        //Display the updated version.
        window.display();
    }

    return 0;
}