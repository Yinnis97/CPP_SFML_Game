#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <cstdlib>

using namespace sf; //hoef ik niet overal sf:: voor te zetten.

void Update(RectangleShape &square, RenderWindow& window);
void Draw(RenderWindow &window, RectangleShape &square);

int main()
{
    VideoMode desktop = VideoMode::getDesktopMode();
    RenderWindow window(desktop, "Game V1.0", Style::None);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    RectangleShape square(Vector2f(100.f, 100.f));
    square.setFillColor(Color::Red);
    square.setPosition(window.getSize().x / 2, window.getSize().x / 2);


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

        Update(square, window);
        Draw(window, square);
 
    }

    return 0;
}

void Update(RectangleShape &square, RenderWindow& window)
{
    if ( Keyboard::isKeyPressed(Keyboard::Q) && square.getPosition().x > 0 )
    {
        square.move(-10.f, 0.f);
    }
    if ( Keyboard::isKeyPressed(Keyboard::D) && square.getPosition().x + square.getSize().x < window.getSize().x )
    {
        square.move(10.f, 0.f);
    }
    if ( Keyboard::isKeyPressed(Keyboard::Z) && square.getPosition().y > 0 )
    {
        square.move(0.f, -10.f);
    }
    if ( Keyboard::isKeyPressed(Keyboard::S) && square.getPosition().y + square.getSize().y < window.getSize().y )
    {
        square.move(0.f, 10.f);
    }

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        square.setFillColor(Color::Blue);
    }
    else
    {
        square.setFillColor(Color::Red);
    }
}


void Draw(RenderWindow& window, RectangleShape &square)
{
    window.clear(Color::Cyan); //Clear : Moet gebeuren vor telkens een nieuwe versie van de display te krijgen.
    window.draw(square);       //Draw the updated version.
    window.display();          //Display the updated version.
}